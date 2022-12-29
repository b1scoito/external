#include "pch.hpp"
#include "glow.hpp"

#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"

void c_glow::run()
{
	while ( var::b_is_running )
	{
		if (!config.visuals.b_glow_enable)
		{
			timer::sleep(1);
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
		if ( !(var::cs::h_wnd == GetForegroundWindow()) )
			continue;

		// Check if in menu
		if ( g_client->in_menu() )
			continue;

		// Check if in a game
		if ( !g_engine->in_game() )
			continue;

		for ( std::int32_t i = 1; i < g_engine->get_max_player_count(); i++ )
		{
			const c_entity entity( g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (i * 0x10) ) );

			if ( !entity.get_entity() )
				continue;

			if ( entity.get_class_id() != (int)sdk::structs::class_index::CCSPlayer )
				continue;

			if ( entity.is_localplayer() )
				continue;

			if ( !entity.is_alive() )
				continue;

			if ( entity.is_dormant() )
				continue;

			if ( !entity.is_enemy() )
				continue;

			if (config.visuals.b_glow_visible_only && !entity.is_visible_ray())
				continue;

			const auto entity_glow_offset = g_client->get_glow_object_manager() + (entity.glow_index() * 0x38);
			auto glow = g_memory->read<sdk::structs::glow_object_t>( entity_glow_offset );

			if (config.visuals.b_glow_health_based) {
				// Health glow
				const auto entity_health = entity.get_health();
				glow.set(
					1.f - (entity_health / 100.f),	// R
					entity_health / 100.f,			// G
					0.f / 255.f,					// B
					config.visuals.f_glow_a			// A
				);
			}
			else {
				glow.set(
					config.visuals.f_glow_r / 255.f,	// R
					config.visuals.f_glow_g / 255.f,	// G
					config.visuals.f_glow_b / 255.f,	// B
					config.visuals.f_glow_a				// A
				);
			}

			g_memory->write<sdk::structs::glow_object_t>( entity_glow_offset, glow ); // Set glow
		}

		const auto end = std::chrono::high_resolution_clock::now();

		// Update last frame and last tick
		last_tick = global_vars.iTickCount;
		last_frame = global_vars.iFrameCount;

		std::chrono::duration<float, std::milli> elapsed = end - start;
		function_elapsed = elapsed.count();
	}
}