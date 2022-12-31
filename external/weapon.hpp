#pragma once

#include "offsets.hpp"

class c_weapon
{
private:
	std::int32_t index = {};
	std::uintptr_t address = {};

public:
	c_weapon(const std::uintptr_t e_address)
	{
		this->address = e_address;

		if (this->address)
			this->index = g_memory->read<std::int16_t>(e_address + sdk::netvars::m_iItemDefinitionIndex);
	}

public: // Read
	constexpr auto& get_weapon_index() const {
		return this->index;
	}
	
	constexpr auto& get_weapon_address() const {
		return this->address;
	}

	sdk::structs::weapon_data_t get_weapon_data() const;
	std::int32_t get_table_index() const;
	std::string get_weapon_name_from_index() const;
};