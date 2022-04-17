#include "pch.hpp"
#include "sdk.hpp"

void c_sdkbase::run()
{
	log_debug("Waiting for CS:GO to open...");

	do
	{
		proc = process::get_by_name(var::game::str_process);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));

	} while (!proc.is_valid());

	g_mem->attach();

	do
	{
		g_mem->get_module(L"engine.dll", engine);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));

	} while (engine.first <= 0x0);

	enginebase = engine.first;
	log_debug("engine.dll address -> 0x%x", enginebase);

	do
	{
		g_mem->get_module(L"client.dll", client);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));

	} while (client.first <= 0x0);

	clientbase = client.first;
	log_debug("client.dll address -> 0x%x", clientbase);

	local_player = g_mem->read<std::int32_t>(clientbase + sdk::offsets::dwLocalPlayer);
	if (!local_player)
	{
		while (!local_player)
		{
			local_player = g_mem->read<std::int32_t>(clientbase + sdk::offsets::dwLocalPlayer);
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
	}

	log_debug("localplayer address -> 0x%x", local_player);
}

bool c_sdkbase::in_game()
{
	const auto client_state = g_mem->read<std::uintptr_t>(this->enginebase + sdk::offsets::dwClientState);
	const auto state = (g_mem->read<int>(client_state + sdk::offsets::dwClientState_State) == 6);

	return state;
}

bool c_sdkbase::in_menu()
{
	CURSORINFO ci { sizeof(CURSORINFO) };
	if (!GetCursorInfo(&ci))
		return false;

	const auto handle = ci.hCursor;
	if ((handle > (HCURSOR)50000) && (handle < (HCURSOR)100000))
		return true;

	return false;
}

c_sdkbase::~c_sdkbase()
{
	g_mem->unload();
}