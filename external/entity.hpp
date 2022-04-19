#pragma once
#include "vector.hpp"

class c_entity
{
private:
	std::uintptr_t base_address = {};

public:
	c_entity(const std::int32_t entity_index = {})
	{
		if (!entity_index)
			base_address = sdk::base->get_local_player();
		else
			base_address = memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (entity_index * 0x10));
	}

	constexpr auto& get_entity() const { return base_address; }

	const auto health() const {
		return memory->read<std::int32_t>(base_address + sdk::netvars::m_iHealth);
	}

	const auto is_dormant() const {
		return memory->read<bool>(base_address + sdk::offsets::m_bDormant);
	}

	const auto team() const {
		return memory->read<std::int32_t>(base_address + sdk::netvars::m_iTeamNum);
	} 

	const auto move_type() const {
		return memory->read<std::uint8_t>(base_address + sdk::netvars::m_MoveType);
	}

	const auto flags() const {
		return memory->read<std::uint8_t>(base_address + sdk::netvars::m_fFlags);
	}

	const auto life_state() const {
		return memory->read<std::int32_t>(base_address + sdk::netvars::m_lifeState);
	}

	const auto glow_index() const {
		return memory->read<std::int32_t>(base_address + sdk::netvars::m_iGlowIndex);
	}

	const auto crosshair_id() const {
		return memory->read<std::int32_t>(base_address + sdk::netvars::m_iCrosshairId);
	}

	const auto bone_matrix(const int& bone) const {
		Vector out = {};

		const auto temp = memory->read<std::ptrdiff_t>(base_address + sdk::netvars::m_dwBoneMatrix);

		out.x = memory->read<float>(temp + 0x30 * bone + 0xC);
		out.y = memory->read<float>(temp + 0x30 * bone + 0x1C);
		out.z = memory->read<float>(temp + 0x30 * bone + 0x2C);

		return out;
	}

	const auto is_alive() const {
		return (this->life_state() == sdk::structs::entity_life_state::LIFE_ALIVE);
	}

	const auto force_jump(const std::int32_t state) const {
		return memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceJump, state);
	}

	const auto force_attack(const std::int32_t state) const {
		return memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceAttack, state);
	}

	const auto is_localplayer() const {
		return base_address == sdk::base->get_local_player();
	}

	const auto has_immunity() const {
		return memory->read<bool>(base_address + sdk::netvars::m_bGunGameImmunity);
	}
};