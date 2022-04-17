#pragma once

class c_entity
{
private:
	std::uintptr_t base_address = {};
	std::int32_t ent_idx = {};

	constexpr auto& get_entity_address()
	{
		if (!ent_idx)
			base_address = sdk::base->get_local_player();
		else
			base_address = memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (ent_idx * 0x10));
	
		return base_address;
	}

public:
	c_entity(const std::int32_t entity_index = {})
	{
		if (entity_index)
			this->ent_idx = entity_index;

		get_entity_address();
	}

	constexpr auto& get_entity() { return base_address; }

	const auto health()
	{
		return memory->read<std::int32_t>(get_entity_address() + sdk::netvars::m_iHealth);
	}

	const auto dormant()
	{
		return memory->read<bool>(get_entity_address() + sdk::offsets::m_bDormant);
	}

	const auto team()
	{
		return memory->read<std::int32_t>(get_entity_address() + sdk::netvars::m_iTeamNum);
	}

	const auto move_type()
	{
		return memory->read<std::uint8_t>(get_entity_address() + sdk::netvars::m_MoveType);
	}

	const auto flags()
	{
		return memory->read<std::uint8_t>(get_entity_address() + sdk::netvars::m_fFlags);
	}

	const auto life_state()
	{
		return memory->read<std::int32_t>(get_entity_address() + sdk::netvars::m_lifeState);
	}

	const auto glow_index()
	{
		return memory->read<std::int32_t>(get_entity_address() + sdk::netvars::m_iGlowIndex);
	}
};