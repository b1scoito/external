#include "pch.hpp"
#include "bhop.hpp"

void c_bhop::run()
{
	log_debug( xorstr( "initializing bhop thread." ) );

	std::thread( [&]
	{
		while ( var::b_is_running )
		{
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

			// Check if space is pressed down
			if ( !(GetAsyncKeyState( VK_SPACE ) & 0x8000) )
				continue;

			// Check if in menu
			if ( g_client->in_menu() )
				continue;

			// Check if in a game
			if ( !g_engine->in_game() )
				continue;

			// Localplayer
			const c_entity localplayer = {};

			// Check if in ladder, noclip or observer
			const auto move_type = localplayer.move_type();
			if ( move_type == sdk::structs::move_type::MOVETYPE_LADDER ||
				move_type == sdk::structs::move_type::MOVETYPE_NOCLIP ||
				move_type == sdk::structs::move_type::MOVETYPE_OBSERVER )
				continue;

			// Check if onground and jump, otherwise set -jump
			if ( (localplayer.get_flags() & sdk::structs::flags::FL_ONGROUND) )
				g_client->force_jump( 5 ); // +jump
			else
				if ( g_client->get_force_jump() == 5 )
					g_client->force_jump( 4 ); // -jump

			auto end = std::chrono::high_resolution_clock::now();

			// Update last frame and last tick
			last_tick = global_vars.iTickCount;
			last_frame = global_vars.iFrameCount;

			std::chrono::duration<float, std::milli> elapsed = end - start;
			function_elapsed = elapsed.count();
		}
	} ).detach();
}