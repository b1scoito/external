#pragma once

#include "engine.hpp" // for g_engine

class c_client
{
public: // Read
	std::tuple<std::uintptr_t, std::int32_t> get_local_player() const;
	bool in_menu() const;
	std::int32_t get_game_type() const;
	std::uintptr_t get_glow_object_manager() const;
	std::int32_t get_force_jump() const;
	std::int32_t get_force_attack() const;

public: // Write
	std::int32_t force_jump(const std::int32_t state) const;
	std::int32_t force_attack(const std::int32_t state) const;
};

inline auto g_client = std::make_unique<c_client>();