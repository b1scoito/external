#include "pch.hpp"
#include "engine.hpp"

const std::uintptr_t c_engine::get_client_state() const
{
	return g_memory->read<std::uintptr_t>(sdk::base->get_engine_image().base + sdk::offsets::dwClientState);
}

const sdk::structs::globalvars_t c_engine::get_globalvars() const
{
	return g_memory->read<sdk::structs::globalvars_t>(sdk::base->get_engine_image().base + sdk::offsets::dwGlobalVars);
}

const std::int32_t c_engine::in_game() const
{
	return g_memory->read<std::int32_t>(this->get_client_state() + sdk::offsets::dwClientState_State) == SIGNONSTATE_FULL;
}

const std::int32_t c_engine::get_max_player_count() const
{
	return g_memory->read<std::int32_t>(this->get_client_state() + sdk::offsets::dwClientState_MaxPlayer);
}

const Vector c_engine::get_view_angles() const
{
	return g_memory->read<Vector>(this->get_client_state() + sdk::offsets::dwClientState_ViewAngles);
}

const bool c_engine::set_view_angles(const Vector view_angles) const
{
	return g_memory->write<Vector>(this->get_client_state() + sdk::offsets::dwClientState_ViewAngles, view_angles);
}