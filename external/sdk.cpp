#include "pch.hpp"
#include "sdk.hpp"

bool c_basesdk::run()
{
	log_debug(xorstr("Waiting for CS:GO to open..."));

	do
	{
		proc = process::get_by_name(var::game::str_process);
		timer::sleep(250);
	} while (!proc.is_running());


	log_debug(xorstr("Attaching to process"));
	g_memory->attach();

	if (!sdk::base->check_for_outdated_offsets())
	{
		log_debug("Cheat is outdated! exiting.");
		timer::sleep(3000);

		return false;
	}

	log_debug(xorstr("Waiting for engine.dll to load..."));
	do
	{
		g_memory->get_module(xorstr(L"engine.dll"), engine);
		timer::sleep(250);
	} while (get_engine_image().base <= 0x0);

	log_debug(xorstr("engine.dll -> 0x%x"), get_engine_image().base);

	log_debug(xorstr("Waiting for client.dll to load..."));
	do
	{
		g_memory->get_module(xorstr(L"client.dll"), client);
		timer::sleep(250);
	} while (get_client_image().base <= 0x0);

	log_debug(xorstr("client.dll -> 0x%x"), get_client_image().base);

	return true;
}

const std::uintptr_t c_basesdk::get_local_player()
{
	auto local_player = g_memory->read<std::uintptr_t>(get_client_image().base + sdk::offsets::dwLocalPlayer);
	if (!local_player)
	{
		while (!local_player)
		{
			local_player = g_memory->read<std::uintptr_t>(get_client_image().base + sdk::offsets::dwLocalPlayer);
			timer::sleep(100);
		}
	}

	return local_player;
}

const std::int32_t c_basesdk::get_max_player_count()
{
	const auto client_state = g_memory->read<std::uintptr_t>(get_engine_image().base + sdk::offsets::dwClientState);
	const auto max_player_count = g_memory->read<std::int32_t>(client_state + sdk::offsets::dwClientState_MaxPlayer);

	return max_player_count;
}

const bool c_basesdk::in_game()
{
	const auto client_state = g_memory->read<std::uintptr_t>(get_engine_image().base + sdk::offsets::dwClientState);
	const auto state = (g_memory->read<int>(client_state + sdk::offsets::dwClientState_State) == SIGNONSTATE_FULL);

	return state;
}

const bool c_basesdk::in_menu() const
{
	CURSORINFO ci { sizeof(CURSORINFO) };
	if (!GetCursorInfo(&ci))
		return false;

	const auto handle = ci.hCursor;
	if ((handle > (HCURSOR)50000) && (handle < (HCURSOR)100000))
		return true;

	return false;
}

const std::int32_t c_basesdk::get_game_type() const
{
	const auto game_rules_proxy = g_memory->read<std::uintptr_t>(sdk::offsets::dwGameRulesProxy);
	const auto game_type = g_memory->read<std::int32_t>(game_rules_proxy + sdk::netvars::m_SurvivalGameRuleDecisionTypes);

	return game_type;
}

const std::uintptr_t c_basesdk::get_glow_object_manager() const
{
	return g_memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwGlowObjectManager);
}

const bool c_basesdk::check_for_outdated_offsets() const
{
	wchar_t filename[MAX_PATH] = {};
	if (!GetModuleFileNameEx(g_memory->get_handle(), NULL, filename, MAX_PATH))
		return false;

	const std::wstring name = filename;
	const auto path = name.substr(0, name.find_last_of(L"/\\")) + L"\\csgo\\steam.inf";

	std::ifstream in(path);
	std::string line;
	if (in.good())
		std::getline(in, line);

	const auto csgo_version = string::split(line, "=")[1];

	if (var::game::current_game_version != csgo_version)
		return false;

	return true;
}

c_basesdk::~c_basesdk()
{
	g_memory->unload();
}