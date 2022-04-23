#include "pch.hpp"
#include "skinchanger.hpp"

std::int32_t get_model_index_by_name(const std::string_view model_name)
{
	const auto client_state = g_memory->read<std::uintptr_t>(sdk::base->get_engine_image().base + sdk::offsets::dwClientState);
	log_debug("client_state: 0x%X", client_state);

	const auto m_dwModelPrecache = g_memory->pattern_scan(sdk::base->get_engine_image().base, "\x0C\x3B\x81\xAA\xAA\xAA\xAA\x75\x11\x8B\x45\x10\x83\xF8\x01\x7C\x09\x50\x83", "");
	log_debug("m_dwModelPrecache: 0x%X", m_dwModelPrecache);
	
	const auto model_precache_offs = g_memory->read<std::int32_t>(client_state + m_dwModelPrecache);
	log_debug("model_precache_offs: 0x%X", model_precache_offs);

	const auto network_str_dict = g_memory->read<std::uintptr_t>(model_precache_offs + 0x40);
	log_debug("network_str_dict: 0x%X", network_str_dict);

	const auto network_str_dict_item = g_memory->read<std::uintptr_t>(network_str_dict + 0xC);
	log_debug("network_str_dict_item: 0x%X", network_str_dict_item);

	for (size_t i = 0; i < 1024; i++)
	{
		const auto item = g_memory->read<std::int32_t>(network_str_dict_item + 0xC + i * 0x34);

		char str[128] = {};
		if (g_memory->read(item, str, sizeof(str)))
		{
			if (str == model_name)
				return i;
		}
	}

	return {};
}

std::int32_t get_model_index(const std::int32_t item_index)
{
	std::int32_t ret = {};
	switch (item_index)
	{
		case sdk::structs::item_definitions::WEAPON_KNIFE:
			ret = get_model_index_by_name("models/weapons/v_knife_default_ct.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_T:
			ret = get_model_index_by_name("models/weapons/v_knife_default_t.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_BAYONET:
			ret = get_model_index_by_name("models/weapons/v_knife_bayonet.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_FLIP:
			ret = get_model_index_by_name("models/weapons/v_knife_flip.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_GUT:
			ret = get_model_index_by_name("models/weapons/v_knife_gut.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_KARAMBIT:
			ret = get_model_index_by_name("models/weapons/v_knife_karam.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_M9_BAYONET:
			ret = get_model_index_by_name("models/weapons/v_knife_m9_bay.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_TACTICAL:
			ret = get_model_index_by_name("models/weapons/v_knife_tactical.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_FALCHION:
			ret = get_model_index_by_name("models/weapons/v_knife_falchion_advanced.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_SURVIVAL_BOWIE:
			ret = get_model_index_by_name("models/weapons/v_knife_survival_bowie.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_BUTTERFLY:
			ret = get_model_index_by_name("models/weapons/v_knife_butterfly.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_PUSH:
			ret = get_model_index_by_name("models/weapons/v_knife_push.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_URSUS:
			ret = get_model_index_by_name("models/weapons/v_knife_ursus.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_GYPSY_JACKKNIFE:
			ret = get_model_index_by_name("models/weapons/v_knife_gypsy_jackknife.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_STILETTO:
			ret = get_model_index_by_name("models/weapons/v_knife_stiletto.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_WIDOWMAKER:
			ret = get_model_index_by_name("models/weapons/v_knife_widowmaker.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_CSS:
			ret = get_model_index_by_name("models/weapons/v_knife_css.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_CORD:
			ret = get_model_index_by_name("models/weapons/v_knife_cord.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_CANIS:
			ret = get_model_index_by_name("models/weapons/v_knife_canis.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_OUTDOOR:
			ret = get_model_index_by_name("models/weapons/v_knife_outdoor.mdl");
			break;
		case sdk::structs::item_definitions::WEAPON_KNIFE_SKELETON:
			ret = get_model_index_by_name("models/weapons/v_knife_skeleton.mdl");
			break;
		default:
			break;
	}

	return ret;
}

void c_skinchanger::run()
{
	log_debug(xorstr("initializing skin changer thread."));

	std::thread([&] {
		while (var::b_is_running)
		{
			// Only update each tick
			const auto global_vars = g_world->get_globalvars();

			const auto update = (global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame);
			// Sleep for performance
			if (!update) // Why does this have to make sense?
				timer::sleep(1.f);
			else
				timer::sleep(1.f);

			// Check if active window is CS:GO
			if (const auto hwnd = FindWindow(xorstr(L"Valve001"), nullptr); !(hwnd == GetForegroundWindow()))
				continue;

			// Check if in menu
			if (sdk::base->in_menu())
				continue;

			// Check if in a game
			if (!sdk::base->in_game())
				continue;

			// Local player
			const c_entity localplayer = {};

			const auto model_index = get_model_index(508); // M9 Bayonet

			// loop through m_hMyWeapons slots (8 will be enough)
			for (size_t i = 0; i < 8; i++)
			{
				// get entity of weapon in current slot
				auto current_weapon = g_memory->read<std::int32_t>(localplayer.get_entity() + sdk::netvars::m_hMyWeapons + i * 0x4);
				current_weapon = g_memory->read<std::int32_t>(sdk::offsets::dwEntityList + (current_weapon - 1) * 0x10);

				if (!current_weapon) 
					continue;

				const auto weapon_index = g_memory->read<std::int32_t>(current_weapon + sdk::netvars::m_iItemDefinitionIndex);

				// for knives, set item and model related properties
				if (weapon_index == sdk::structs::item_definitions::WEAPON_KNIFE || weapon_index == sdk::structs::item_definitions::WEAPON_KNIFE_T)
				{
					g_memory->write<std::int32_t>(current_weapon + sdk::netvars::m_iItemDefinitionIndex, 562);
					g_memory->write<std::int32_t>(current_weapon + 0x258, model_index); // m_nModelIndex
					g_memory->write<std::int32_t>(current_weapon + sdk::netvars::m_nViewModelIndex, model_index);
					g_memory->write<std::int32_t>(current_weapon + sdk::netvars::m_iEntityQuality, 3);
				}
			}

			// get entity of weapon in our hands
			auto active_weapon = g_memory->read<std::int32_t>(localplayer.get_entity() + sdk::netvars::m_hActiveWeapon);
			active_weapon = g_memory->read<std::int32_t>(sdk::offsets::dwEntityList + (active_weapon - 1) * 0x10);
			if (!active_weapon) 
				continue;
	
			// get viewmodel entity
			auto view_model = g_memory->read<std::int32_t>(localplayer.get_entity() + sdk::netvars::m_hViewModel);
			view_model = g_memory->read<std::int32_t>(sdk::offsets::dwEntityList + (view_model - 1) * 0x10);
			if (!view_model)
				continue;

			g_memory->write<std::int32_t>(view_model + 0x258, model_index);

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
		}).detach();
}