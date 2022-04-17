#include "pch.hpp"
#include "sdk.hpp"

void c_basesdk::run()
{
	log_debug("Waiting for CS:GO to open...");

	do
	{
		proc = process::get_by_name(var::game::str_process);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	} 
	while (!proc.is_valid());

	g_mem->attach();

	do
	{
		g_mem->get_module(L"engine.dll", engine);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	} 
	while (engine.first <= 0x0);

	log_debug("engine.dll address -> 0x%X", get_engine_image().base);

	do
	{
		g_mem->get_module(L"client.dll", client);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	} 
	while (client.first <= 0x0);

	log_debug("client.dll address -> 0x%X", get_client_image().base);
}

std::uintptr_t c_basesdk::get_local_player()
{
	auto local_player = g_mem->read<std::int32_t>(get_client_image().base + sdk::offsets::dwLocalPlayer);
	if (!local_player)
	{
		while (!local_player)
		{
			local_player = g_mem->read<std::int32_t>(get_client_image().base + sdk::offsets::dwLocalPlayer);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	return local_player;
}

bool c_basesdk::in_game()
{
	const auto client_state = g_mem->read<std::uintptr_t>(get_engine_image().base + sdk::offsets::dwClientState);
	const auto state = (g_mem->read<int>(client_state + sdk::offsets::dwClientState_State) == SIGNONSTATE_FULL);

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
	g_mem->unload();
}