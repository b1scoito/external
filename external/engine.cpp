#include "pch.hpp"
#include "engine.hpp"

std::uintptr_t c_engine::get_client_state() const
{
	return g_memory->read<std::uintptr_t>(sdk::base->get_engine_image().base + sdk::offsets::dwClientState);
}

sdk::structs::globalvars_t c_engine::get_globalvars() const
{
	return g_memory->read<sdk::structs::globalvars_t>(sdk::base->get_engine_image().base + sdk::offsets::dwGlobalVars);
}

std::int32_t c_engine::in_game() const
{
	return g_memory->read<std::int32_t>(this->get_client_state() + sdk::offsets::dwClientState_State) == SIGNONSTATE_FULL;
}

std::int32_t c_engine::get_max_player_count() const
{
	return g_memory->read<std::int32_t>(this->get_client_state() + sdk::offsets::dwClientState_MaxPlayer);
}

Vector c_engine::get_view_angles() const
{
	return g_memory->read<Vector>(this->get_client_state() + sdk::offsets::dwClientState_ViewAngles);
}

std::string c_engine::get_map_name()
{
	auto map_directory = std::make_unique<char[]>(255);
	if (!g_memory->read(this->get_client_state() + sdk::offsets::dwClientState_MapDirectory, map_directory.get(), 255))
		return {};

	return std::string(map_directory.get());
}

std::string c_engine::get_game_directory()
{
	auto game_directory = std::make_unique<char[]>(255);
	if (!g_memory->read(sdk::base->get_engine_image().base + sdk::offsets::dwGameDir, game_directory.get(), 255))
		return {};

	return std::string(game_directory.get());
}

bool c_engine::set_view_angles(Vector view_angles) const
{
	return g_memory->write<Vector>(this->get_client_state() + sdk::offsets::dwClientState_ViewAngles, view_angles);
}

std::int32_t c_engine::force_full_update() const
{
	return g_memory->write<std::int32_t>(this->get_client_state() + sdk::offsets::clientstate_delta_ticks, -1);
}

std::uintptr_t c_engine::get_user_info_table() const
{
	return g_memory->read<std::uintptr_t>(this->get_client_state() + sdk::offsets::dwClientState_PlayerInfo);
}
