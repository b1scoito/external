#pragma once

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
	constexpr auto &get_entity() const
	{
		return this->base_address;
	}

	constexpr auto &get_entity_index() const
	{
		return this->index;
	}

	const std::int32_t health() const;
	const std::int32_t get_team() const;
	const std::int32_t get_flags() const;
	const std::int32_t glow_index() const;
	const std::int32_t crosshair_id() const;
	const bool is_dormant() const;
	const bool is_scoped() const;
	const bool is_spotted() const;
	const bool is_visible_ray() const;
	const bool has_immunity() const;
	const std::int32_t move_type() const;
	const std::int32_t life_state() const;
	const Vector get_velocity() const;
	const std::int32_t get_class_id() const;
	const Vector bone_matrix(const int &bone) const;
	const Vector eye_position() const;
	const bool is_alive() const;
	const std::uintptr_t get_view_model() const;
	const Vector aim_punch() const;
	const bool is_localplayer() const;
	// From: https://github.com/rollraw/qo0-base/blob/f6ded6392dbb9e433c279fdb6fc3843398b9e1c7/base/sdk/entity.cpp#L212
	const bool is_enemy() const;
};

inline auto g_local = c_entity();