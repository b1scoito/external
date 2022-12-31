#include "pch.hpp"
#include "skinchanger.hpp"

void c_skinchanger::populate_models()
{
	const auto client_state = g_engine->get_client_state();
	const auto network_string_table = g_memory->read<std::uintptr_t>(client_state + 0x52A4); // m_dwModelPrecache
	const auto network_string_dictionary = g_memory->read<std::uintptr_t>(network_string_table + 0x40);
	const auto network_string_dictionary_item_first = g_memory->read<std::uintptr_t>(network_string_dictionary + 0xC);

	for (int i = 0; i < 1024; i++)
	{
		const auto mpc_name_ptr = g_memory->read<std::uintptr_t>(network_string_dictionary_item_first + 0xC + (i * 0x34));
		if (!mpc_name_ptr)
			continue;

		auto mpc_read_name = std::make_unique<char[]>(255);
		if (g_memory->read(mpc_name_ptr, mpc_read_name.get(), 255))
			g_model_index_list[mpc_read_name.get()] = i;
	}
}

std::int32_t c_skinchanger::find_model_index_by_name(std::string_view model_name)
{
	const auto it = g_model_index_list.find(model_name.data());
	if (it == g_model_index_list.end())
		return {};

	return it->second;
}

// From: https://github.com/0xf1a/xSkins
void c_skinchanger::run()
{
	while ( var::b_is_running )
	{
		if (!config.visuals.b_sc_enable) {
			timer::sleep(1);
			continue;
		}

		if (!g_engine->in_game())
			continue;

		if (!g_local.get_entity())
			continue;

		if (!g_local.is_alive())
			continue;

		if (!g_local.get_view_model())
			continue;

		if (var::skins::models.empty())
			continue;

		auto target_knife = (int)sdk::structs::e_item_definitions::WEAPON_KNIFE_M9_BAYONET;
		auto model_index = find_model_index_by_name("models/weapons/v_knife_m9_bay.mdl");

		for (const auto& [weapon_id, weapon_info] : sdk::structs::m_item_list)
		{
			if (weapon_info.name == var::skins::models[config.visuals.i_sc_selected_model_index])
			{
				target_knife = weapon_id;
				model_index = find_model_index_by_name(weapon_info.model);
			}
		}

		for ( size_t i = 0; i < 8; i++ )
		{
			const auto current_weapon = g_memory->read<std::uintptr_t>( (g_local.get_entity() + sdk::netvars::m_hMyWeapons) + i * 0x4 );
			if (!current_weapon)
				continue;
				
			const auto current_weapon_entity = g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + ((current_weapon & 0xFFF) - 1) * 0x10 );
			if ( !current_weapon_entity )
				continue;

			const auto weapon_index = g_memory->read<std::int16_t>( current_weapon_entity + sdk::netvars::m_iItemDefinitionIndex );
			if ( weapon_index == sdk::structs::WEAPON_KNIFE || weapon_index == sdk::structs::WEAPON_KNIFE_T || weapon_index == target_knife)
			{
				g_memory->write<std::int16_t>( current_weapon_entity + sdk::netvars::m_iItemDefinitionIndex, target_knife);
				g_memory->write<std::int32_t>( current_weapon_entity + sdk::netvars::m_nModelIndex, model_index );
				g_memory->write<std::int32_t>( current_weapon_entity + sdk::netvars::m_iViewModelIndex, model_index );
				g_memory->write<std::int32_t>( current_weapon_entity + sdk::netvars::m_iEntityQuality, 3 );
					
				// Skins
				if (config.visuals.b_sc_set_paint_kit && !var::skins::str_paint_kit.empty())
				{
					g_memory->write<std::int32_t>(current_weapon_entity + sdk::netvars::m_iItemIDHigh, -1);
					g_memory->write<std::int32_t>(current_weapon_entity + sdk::netvars::m_nFallbackPaintKit, std::stoi(var::skins::str_paint_kit));
					g_memory->write<float>(current_weapon_entity + sdk::netvars::m_flFallbackWear, 0.0001f);
				}
			}
		}

		const auto active_weapon = g_memory->read<std::uintptr_t>( g_local.get_entity() + sdk::netvars::m_hActiveWeapon );
		if (!active_weapon)
			continue;
			
		const auto active_weapon_entity = g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + ((active_weapon & 0xFFF) - 1) * 0x10 );
		if ( !active_weapon_entity )
			continue;

		const auto weapon_index = g_memory->read<std::int16_t>( active_weapon_entity + sdk::netvars::m_iItemDefinitionIndex );
		if ( weapon_index != target_knife )
			continue;

		const auto view_model_entity = g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + ((g_local.get_view_model() & 0xFFF) - 1) * 0x10);
		if ( !view_model_entity )
			continue;

		g_memory->write<std::int32_t>( view_model_entity + sdk::netvars::m_nModelIndex, model_index );
	}
}