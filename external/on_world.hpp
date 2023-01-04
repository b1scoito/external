#pragma once 

#include "pch.hpp"
#include "convar.hpp"

inline void on_world_cache() {
	while (var::b_is_running)
	{
		// Clear variables outside game
		if (!g_engine->in_game())
		{
			g_local = c_entity();
			g_convar_list.clear();
			g_model_index_list.clear();

			continue;
		}

		// Parse BSP when in game
		static std::string current_map;
		std::string map = g_engine->get_map_name();
		if (map != current_map) {
			current_map = map;
			var::bsp::parsed_map = var::bsp::bp.load_map(g_engine->get_game_directory(), g_engine->get_map_name());
			if (!var::bsp::parsed_map)
				std::cerr << "Failed to load map into BSP parser!\n";
		}

		// Populate localplayer if none
		if (!g_local.get_entity())
		{
			const auto [addr, index] = g_client->get_local_player();
			g_local = c_entity(addr, index);
		}

		// Populate model vector if none
		if (var::skins::models.empty())
		{
			for (const auto& [weapon_id, weapon_info] : sdk::structs::m_item_list) {
				if (weapon_id > sdk::structs::WEAPON_KNIFE_BAYONET && weapon_id < sdk::structs::WEAPON_KNIFE_SKELETON)
					var::skins::models.emplace_back(weapon_info.name);
			}
		}

		// Populate convar list if none
		if (g_convar_list.empty())
			g_convar->populate_convars();

		// Populate model index list if none
		if (g_model_index_list.empty())
			g_skinchanger->populate_models();

		timer::sleep(1000);
	}
}