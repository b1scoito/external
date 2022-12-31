#pragma once

#include "convar.hpp"
#include "weapon.hpp"
#include "engine.hpp"

class c_entity
{
private:
	std::int32_t index = {};
	std::uintptr_t base_address = {};

public:
	c_entity() = default;
	c_entity(const std::uintptr_t base_addr, const std::int32_t e_index = {})
	{
		this->base_address = base_addr;
		this->index = e_index;
	}

public: // Read
	constexpr auto &get_entity() const{
		return this->base_address;
	}

	constexpr auto &get_entity_index() const {
		return this->index;
	}

	std::int32_t get_health() const;
	std::int32_t get_team() const;
	std::int32_t get_flags() const;
	std::int32_t glow_index() const;
	std::int32_t crosshair_id() const;
	bool is_dormant() const;
	bool is_scoped() const;
	bool is_spotted() const;
	bool is_visible_ray() const;
	bool has_immunity() const;
	std::int32_t move_type() const;
	std::int32_t life_state() const;
	Vector get_velocity() const;
	std::int32_t get_class_id() const;
	Vector bone_matrix(int bone) const;
	Vector eye_pos() const;
	Vector view_offset() const;
	Vector origin() const;
	bool is_alive() const;
	std::uintptr_t get_view_model() const;
	Vector aim_punch() const;
	bool is_localplayer() const;
	// From: https://github.com/rollraw/qo0-base/blob/f6ded6392dbb9e433c279fdb6fc3843398b9e1c7/base/sdk/entity.cpp#L212
	bool is_enemy() const;
	c_weapon get_weapon() const;
	sdk::structs::playerinfo_t get_player_info() const;
};

inline auto g_local = c_entity();