#include "pch.hpp"
#include "weapon.hpp"

// Thanks to: https://www.unknowncheats.me/forum/counterstrike-global-offensive/408596-ccsweapondata-itemdefinitionindex-internal-external.html
sdk::structs::weapon_data_t c_weapon::get_weapon_data() const {
	auto weapon_table = g_memory->read<sdk::structs::weapon_info_table_t>(sdk::base->get_client_image().base + sdk::offsets::dwWeaponTable);

	for (std::int16_t i = 0; i <= weapon_table.last_index; i++)
	{
		auto current_weapon = g_memory->read<sdk::structs::weapon_info_table_object_t>((std::uintptr_t)weapon_table.weapon_table + sizeof(sdk::structs::weapon_info_table_object_t) * i); // weapon_data_t* pWeaponInfo; 0x000C WeaponInfo*
		if (current_weapon.item_definition_index == this->index)
			return g_memory->read<sdk::structs::weapon_data_t>((std::uintptr_t)current_weapon.weapon_info);
	}

	return {};
}

std::int32_t c_weapon::get_table_index() const {
	return g_memory->read<std::int32_t>(this->address + sdk::offsets::dwWeaponTableIndex);
}

std::string c_weapon::get_weapon_name_from_index() const {
	for (const auto& [weapon_id, weapon_info] : sdk::structs::m_item_list)
	{
		if (weapon_id == this->index)
			return std::string(weapon_info.name);
	}

	return {};
}