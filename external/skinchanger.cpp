#include "pch.hpp"
#include "skinchanger.hpp"

#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"

void c_skinchanger::populate_model_index_list()
{
	const auto client_state = g_engine->get_client_state();
	const auto network_string_table = g_memory->read<std::uintptr_t>( client_state + 0x52A4 );
	const auto network_string_dictionary = g_memory->read<std::uintptr_t>( network_string_table + 0x40 );
	const auto network_string_dictionary_item_first = g_memory->read<std::uintptr_t>( network_string_dictionary + 0xC );

	for ( int i = 0; i < 1024; i++ )
	{
		const auto mpc_name_ptr = g_memory->read<std::uintptr_t>( network_string_dictionary_item_first + 0xC + (i * 0x34) );
		if ( !mpc_name_ptr )
			continue;

		auto mpc_read_name = std::make_unique<char[]>( 255 );
		if ( g_memory->read( mpc_name_ptr, mpc_read_name.get(), 255 ) )
			g_model_index_list[mpc_read_name.get()] = i;
	}
}

std::int32_t c_skinchanger::find_model_index_by_name( std::string_view model_name )
{
	const auto it = g_model_index_list.find( model_name.data() );
	if ( it == g_model_index_list.end() )
		return {};

	return it->second;
}

// From: https://github.com/0xf1a/xSkins
void c_skinchanger::run( keybind& keybd )
{
	log_debug( xorstr( "initializing skin changer thread." ) );

	std::thread( [&]
	{
		while ( var::b_is_running )
		{
			if ( !keybd.get() )
			{
				timer::sleep( 1 );
				continue;
			}

			// Check if active window is CS:GO
			if ( !(var::game::wnd == GetForegroundWindow()) )
				continue;

			// Check if in menu
			if ( g_client->in_menu() )
				continue;

			// Check if in a game
			if ( !g_engine->in_game() )
				continue;

			const auto model_index = find_model_index_by_name( "models/weapons/v_knife_m9_bay.mdl" );;

			for ( size_t i = 0; i < 8; i++ )
			{
				auto current_weapon = g_memory->read<std::uintptr_t>( (g_local.get_entity() + sdk::netvars::m_hMyWeapons) + i * 0x4 ) & 0xFFF;
				current_weapon = g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (current_weapon - 1) * 0x10 );

				if ( !current_weapon )
					continue;

				const auto weapon_index = g_memory->read<std::int16_t>( current_weapon + sdk::netvars::m_iItemDefinitionIndex );
				if ( weapon_index == sdk::structs::WEAPON_KNIFE || weapon_index == sdk::structs::WEAPON_KNIFE_T || weapon_index == 508 )
				{
					g_memory->write<std::int16_t>( current_weapon + sdk::netvars::m_iItemDefinitionIndex, sdk::structs::WEAPON_KNIFE_M9_BAYONET );
					g_memory->write<std::int32_t>( current_weapon + sdk::netvars::m_nModelIndex, model_index );
					g_memory->write<std::int32_t>( current_weapon + sdk::netvars::m_iViewModelIndex, model_index );
					g_memory->write<std::int32_t>( current_weapon + sdk::netvars::m_iEntityQuality, 3 );
				}
			}

			auto active_weapon = g_memory->read<std::uintptr_t>( g_local.get_entity() + sdk::netvars::m_hActiveWeapon ) & 0xFFF;
			active_weapon = g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (active_weapon - 1) * 0x10 );
			if ( !active_weapon )
				continue;

			const auto weapon_index = g_memory->read<std::int16_t>( active_weapon + sdk::netvars::m_iItemDefinitionIndex );
			if ( weapon_index != sdk::structs::WEAPON_KNIFE_M9_BAYONET )
				continue;

			auto view_model = g_memory->read<std::uintptr_t>( g_local.get_entity() + sdk::netvars::m_hViewModel ) & 0xFFF;
			view_model = g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (view_model - 1) * 0x10 );
			if ( !view_model )
				continue;

			g_memory->write<std::int32_t>( view_model + sdk::netvars::m_nModelIndex, model_index );
		}
	} ).detach();
}