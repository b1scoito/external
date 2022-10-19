#pragma once

class c_client
{
public: // Read
	const std::tuple<std::uintptr_t, std::int32_t> get_local_player() const;
	const bool in_menu() const;
	const std::int32_t get_game_type() const;
	const std::uintptr_t get_glow_object_manager() const;
	const std::int32_t get_force_jump() const;
	const std::int32_t get_force_attack() const;

public: // Write
	const std::int32_t force_jump( const std::int32_t state ) const;
	const std::int32_t force_attack( const std::int32_t state ) const;
};

inline auto g_client = std::make_unique<c_client>();