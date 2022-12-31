#pragma once

class c_engine
{
public: // Read
	std::uintptr_t get_client_state() const;
	sdk::structs::globalvars_t get_globalvars() const;
	std::int32_t in_game() const;
	std::int32_t get_max_player_count() const;
	Vector get_view_angles() const;
	std::string get_map_name();
	std::string get_game_directory();

public: // Write
	bool set_view_angles(Vector view_angles) const;
	std::int32_t force_full_update() const;
	std::uintptr_t get_user_info_table() const;
};

inline auto g_engine = std::make_unique<c_engine>();