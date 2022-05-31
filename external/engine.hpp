#pragma once

class c_engine
{
public: // Read
	const std::uintptr_t get_client_state() const;
	const sdk::structs::globalvars_t get_globalvars() const;
	const std::int32_t in_game() const;
	const std::int32_t get_max_player_count() const;
};

inline auto g_engine = std::make_unique<c_engine>();