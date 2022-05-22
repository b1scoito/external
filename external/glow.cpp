#include "pch.hpp"
#include "glow.hpp"

void c_glow::run( keybind& keybd )
{
	log_debug( xorstr( "initializing glow thread." ) );

	std::thread( [&]
	{
		while ( var::b_is_running )
		{
			if ( !keybd.get() )
			{
				timer::sleep( 1 );
				continue;
			}

			// Only update each tick
			const auto global_vars = g_engine->get_globalvars();
			const auto update = (global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame);
			if ( !update )
			{
				timer::sleep( global_vars.flIntervalPerTick );
				continue;
			}

			float sleep_time = (function_elapsed - global_vars.flAbsFrameTime);
			timer::sleep( sleep_time );

			auto start = std::chrono::high_resolution_clock::now();

			// Check if active window is CS:GO
			if ( !(var::game::wnd == GetForegroundWindow()) )
				continue;

			// Check if in menu
			if ( g_client->in_menu() )
				continue;

			// Check if in a game
			if ( !g_engine->in_game() )
				continue;

			// Local player
			const c_entity localplayer = {};

			for ( std::int32_t i = 0; i < g_engine->get_max_player_count(); i++ )
			{
				const c_entity entity( i );

				if ( !entity.get_entity() )
					continue;

				if ( entity.is_localplayer() )
					continue;

				if ( !entity.is_alive() )
					continue;

				if ( entity.is_dormant() )
					continue;

				if ( localplayer.get_team() == entity.get_team() )
					continue;

				const auto entity_glow_offset = g_client->get_glow_object_manager() + (entity.glow_index() * 0x38);
				auto glow = g_memory->read<sdk::structs::glow_object_t>( entity_glow_offset );

				// Health glow
				const auto entity_health = entity.get_health();
				glow.set(
					1.f - (entity_health / 100.f),	// R
					entity_health / 100.f,			// G
					0.f / 255.f,					// B
					0.8f							// A
				);

				mutex.lock();
				g_memory->write<sdk::structs::glow_object_t>( entity_glow_offset, glow ); // Set glow
				mutex.unlock();
			}

			auto end = std::chrono::high_resolution_clock::now();

			// Update last frame and last tick
			last_tick = global_vars.iTickCount;
			last_frame = global_vars.iFrameCount;

			std::chrono::duration<float, std::milli> elapsed = end - start;
			function_elapsed = elapsed.count();
		}
	} ).detach();
}