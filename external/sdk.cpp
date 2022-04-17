#include "pch.hpp"
#include "sdk.hpp"

void c_basesdk::run()
{
	log_debug("Waiting for CS:GO to open...");

	process proc = {};
	do
	{
		proc = process::get_by_name(var::game::str_process);
		std::this_thread::sleep_for(250ms);
	} while (!proc.is_valid());

	log_debug("Attaching to process");
	memory->attach();

	log_debug("Waiting for engine.dll to load...");
	do
	{
		memory->get_module(L"engine.dll", engine);
		std::this_thread::sleep_for(250ms);
	} while (get_engine_image().base <= 0x0);

	log_debug("engine.dll -> 0x%x", get_engine_image().base);

	log_debug("Waiting for client.dll to load...");
	do
	{
		memory->get_module(L"client.dll", client);
		std::this_thread::sleep_for(250ms);
	} while (get_client_image().base <= 0x0);

	log_debug("client.dll -> 0x%x", get_client_image().base);
}

std::uintptr_t c_basesdk::get_local_player()
{
	auto local_player = memory->read<std::uintptr_t>(get_client_image().base + sdk::offsets::dwLocalPlayer);
	if (!local_player)
	{
		while (!local_player)
		{
			local_player = memory->read<std::uintptr_t>(get_client_image().base + sdk::offsets::dwLocalPlayer);
			std::this_thread::sleep_for(100ms);
		}
	}

	return local_player;
}

std::int32_t c_basesdk::get_max_player_count()
{
	const auto client_state = memory->read<std::uintptr_t>(get_engine_image().base + sdk::offsets::dwClientState);
	const auto max_player_count = memory->read<std::int32_t>(client_state + sdk::offsets::dwClientState_MaxPlayer);

	return max_player_count;
}

bool c_basesdk::in_game()
{
	const auto client_state = memory->read<std::uintptr_t>(get_engine_image().base + sdk::offsets::dwClientState);
	const auto state = (memory->read<int>(client_state + sdk::offsets::dwClientState_State) == SIGNONSTATE_FULL);

	return state;
}

bool c_basesdk::in_menu()
{
	CURSORINFO ci { sizeof(CURSORINFO) };
	if (!GetCursorInfo(&ci))
		return false;

	const auto handle = ci.hCursor;
	if ((handle > (HCURSOR)50000) && (handle < (HCURSOR)100000))
		return true;

	return false;
}

c_basesdk::~c_basesdk()
{
	memory->unload();
}