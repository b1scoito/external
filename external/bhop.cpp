#include "pch.hpp"
#include "bhop.hpp"

#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"

void c_bhop::run()
{
	log_debug(xorstr("initializing bhop thread."));

	std::thread([&]
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

			const auto frametime = global_vars.flAbsFrameTime;
			const auto delay = (function_elapsed - (frametime < global_vars.flIntervalPerTick ? (frametime * 0.5f) : frametime));
			const auto sleep = std::min( delay, (frametime * 1000) );

			timer::sleep( sleep );

			const auto start = std::chrono::high_resolution_clock::now();

			// Check if active window is CS:GO
			if ( !(var::game::wnd == GetForegroundWindow()) )
				continue;

			// Check if space is pressed down
			if ( !(LI_FN(GetAsyncKeyState).cached()( VK_SPACE ) & 0x8000) )
				continue;

			// Check if in menu
			if ( g_client->in_menu() )
				continue;

			// Check if in a game
			if ( !g_engine->in_game() )
				continue;

			// Check if in ladder, no clip or observer
			const auto move_type = g_local.move_type();
			if ( move_type == sdk::structs::move_type::MOVETYPE_LADDER ||
				move_type == sdk::structs::move_type::MOVETYPE_NOCLIP ||
				move_type == sdk::structs::move_type::MOVETYPE_OBSERVER )
				continue;

			// Check if on ground and jump, otherwise set -jump
			if ( (g_local.get_flags() & sdk::structs::flags::FL_ONGROUND) )
				g_client->force_jump( 5 ); // +jump
			else
				if (g_client->get_force_jump() == 5)
					g_client->force_jump( 4 ); // -jump

			const auto end = std::chrono::high_resolution_clock::now();

			// Update last frame and last tick
			last_tick = global_vars.iTickCount;
			last_frame = global_vars.iFrameCount;

			std::chrono::duration<float, std::milli> elapsed = end - start;
			function_elapsed = elapsed.count();
		} })
		.detach();
}