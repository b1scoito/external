#pragma once

class c_entity
{
private:

public:
	std::uintptr_t base_address = {};

	c_entity(const std::int32_t entity_index = {})
	{
		if (!entity_index)
		{
			base_address = sdk::base->get_local_player();
			log_debug("localplayer -> 0x%X", base_address);
		}
		else
		{
			base_address = memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (entity_index * 0x10));
			log_debug("entity -> 0x%X", base_address);
		}
	}

	const auto health() const
	{
		return memory->read<std::int32_t>(base_address + sdk::netvars::m_iHealth);
	}

	const auto dormant() const
	{
		return memory->read<bool>(base_address + sdk::offsets::m_bDormant);
	}

	const auto team() const
	{
		return memory->read<std::int32_t>(base_address + sdk::netvars::m_iTeamNum);
	}

	const auto move_type() const
	{
		return memory->read<std::uint8_t>(base_address + sdk::netvars::m_MoveType);
	}

	const auto flags() const
	{
		return memory->read<std::uint8_t>(base_address + sdk::netvars::m_fFlags);
	}
};

inline auto entity = std::make_unique<c_entity>();