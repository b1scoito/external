#pragma once

class c_engine
{
public: // Read
	const std::uintptr_t get_client_state() const;
	const sdk::structs::globalvars_t get_globalvars() const;
	const std::int32_t in_game() const;
	const std::int32_t get_max_player_count() const;
	const Vector get_view_angles() const;

public: // Write
	const bool set_view_angles(const Vector view_angles) const;
	const std::int32_t force_full_update() const;
	const std::string get_map_name();
	const std::string get_game_directory();
};

inline auto g_engine = std::make_unique<c_engine>();