#include "pch.hpp"
#include "triggerbot.hpp"

#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"

void c_triggerbot::run( keybind& keybd )
{
	log_debug( xorstr( "initializing triggerbot thread." ) );

	std::thread( [&]
	{
		while ( var::b_is_running )
		{
			timer::sleep( 1 );

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

			const auto frametime = global_vars.flAbsFrameTime;
			const auto delay = (function_elapsed - (frametime < global_vars.flIntervalPerTick ? (frametime * 0.5f) : frametime));
			const auto sleep = std::min( delay, (frametime * 1000) );

			timer::sleep( sleep );

			const auto start = std::chrono::high_resolution_clock::now();

			// Check if active window is CS:GO
			if ( !(var::game::wnd == GetForegroundWindow()) )
				continue;

			// Check if in menu
			if ( g_client->in_menu() )
				continue;

			// Check if in a game
			if ( !g_engine->in_game() )
				continue;

			const auto crosshair_id = g_local.crosshair_id();
			const c_entity entity( g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + ((crosshair_id - 1) * 0x10) ) );

			if ( !entity.get_entity() )
				continue;

			if ( !entity.is_enemy() )
				continue;

			if ( entity.has_immunity() )
				continue;

			if ( crosshair_id > 0 && crosshair_id <= 64 )
			{
				auto delay = random::range( 15.f, 35.f );
				if ( g_local.is_scoped() ) // If scoped, wait more
					delay = random::range( 45.f, 75.f );

				timer::sleep( delay );
				g_client->force_attack( 6 ); // +attack
			}

			const auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<float, std::milli> elapsed = end - start;
			function_elapsed = elapsed.count();

			// Update last frame and last tick
			last_tick = global_vars.iTickCount;
			last_frame = global_vars.iFrameCount;
		}
	} ).detach();
}