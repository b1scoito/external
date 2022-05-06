#pragma once

class c_engine
{
public:
	const auto get_client_state() const
	{
		return g_memory->read<std::uintptr_t>( sdk::base->get_engine_image().base + sdk::offsets::dwClientState );
	}

	const auto get_globalvars() const
	{
		return g_memory->read<sdk::structs::globalvars_t>( sdk::base->get_engine_image().base + sdk::offsets::dwGlobalVars );
	}

	const auto in_game() const
	{
		return g_memory->read<std::int32_t>( this->get_client_state() + sdk::offsets::dwClientState_State ) == SIGNONSTATE_FULL;
	}

	const auto get_max_player_count() const
	{
		return g_memory->read<std::int32_t>( this->get_client_state() + sdk::offsets::dwClientState_MaxPlayer );
	}
};

inline auto g_engine = std::make_unique<c_engine>();