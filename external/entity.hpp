#pragma once
#include "vector.hpp"

class c_entity
{
private:
	std::uintptr_t base_address = {};

public: // Read
	c_entity(const std::int32_t entity_index = {})
	{
		if (!entity_index)
			base_address = sdk::base->get_local_player();
		else
			base_address = g_memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (entity_index * 0x10));
	}

	constexpr auto& get_entity() const { return base_address; }

	const auto get_health() const {
		return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iHealth);
	}

	const auto is_dormant() const {
		return g_memory->read<bool>(base_address + sdk::offsets::m_bDormant);
	}

	const auto get_team() const {
		return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iTeamNum);
	} 

	const auto move_type() const {
		return g_memory->read<std::uint8_t>(base_address + sdk::netvars::m_MoveType);
	}

	const auto get_flags() const {
		return g_memory->read<std::uint8_t>(base_address + sdk::netvars::m_fFlags);
	}

	const auto life_state() const {
		return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_lifeState);
	}

	const auto glow_index() const {
		return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iGlowIndex);
	}

	const auto crosshair_id() const {
		return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iCrosshairId);
	}

	const auto has_immunity() const {
		return g_memory->read<bool>(base_address + sdk::netvars::m_bGunGameImmunity);
	}

	const auto get_velocity() const {
		return g_memory->read<Vector>(base_address + sdk::netvars::m_vecVelocity);
	}

	const auto bone_matrix(const int& bone) const {
		const auto matrix = g_memory->read<std::ptrdiff_t>(base_address + sdk::netvars::m_dwBoneMatrix);

		Vector vec_matrix = {};
		vec_matrix.x = g_memory->read<float>(matrix + 0x30 * bone + 0xC);
		vec_matrix.y = g_memory->read<float>(matrix + 0x30 * bone + 0x1C);
		vec_matrix.z = g_memory->read<float>(matrix + 0x30 * bone + 0x2C);

		return vec_matrix;
	}

	const auto is_alive() const {
		return this->life_state() == sdk::structs::life_state::LIFE_ALIVE;
	}

	const auto is_localplayer() const {
		return base_address == sdk::base->get_local_player();
	}


public: // Write
	const auto force_jump(const std::int32_t state) const {
		return g_memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceJump, state);
	}

	const auto force_attack(const std::int32_t state) const {
		return g_memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceAttack, state);
	}
};