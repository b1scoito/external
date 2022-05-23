#include "pch.hpp"
#include "triggerbot.hpp"

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
			const auto delay = (function_elapsed - (frametime < 1 / (1.f / global_vars.flIntervalPerTick) ? (frametime * 0.5f) : frametime));
			const auto sleep = std::min( delay, (global_vars.flIntervalPerTick * 1000) );

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

			// Localplayer
			const c_entity localplayer = {};

			const auto crosshair_id = localplayer.crosshair_id();
			const c_entity entity( crosshair_id - 1 );

			if ( !entity.get_entity() )
				continue;

			if ( (entity.get_team() > sdk::structs::team_id::TEAM_SPECTATOR) && (localplayer.get_team() == entity.get_team()) )
				continue;

			if ( entity.has_immunity() )
				continue;

			if ( crosshair_id > 0 && crosshair_id <= 64 )
				g_client->force_attack( 6 ); // +attack

			const auto end = std::chrono::high_resolution_clock::now();

			std::chrono::duration<float, std::milli> elapsed = end - start;
			function_elapsed = elapsed.count();

			// Update last frame and last tick
			last_tick = global_vars.iTickCount;
			last_frame = global_vars.iFrameCount;
		}
	} ).detach();
}