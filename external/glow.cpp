#include "pch.hpp"
#include "glow.hpp"

void c_glow::run(keybind& keybd)
{
	log_debug(xorstr("initializing glow thread."));

	std::thread([&] {
		while (var::b_is_running)
		{
			if (!keybd.get())
			{
				timer::sleep(50);
				continue;
			}

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

			for (std::int32_t i = 0; i < sdk::base->get_max_player_count(); i++)
			{
				const c_entity entity(i);

				if (!entity.get_entity())
					continue;

				if (entity.is_localplayer())
					continue;

				if (!entity.is_alive())
					continue;

				if (entity.is_dormant())
					continue;

				if (localplayer.get_team() == entity.get_team())
					continue;
				
				const auto entity_glow_offset = sdk::base->get_glow_object_manager() + (entity.glow_index() * 0x38);
				auto glow = g_memory->read<sdk::structs::glow_object_t>(entity_glow_offset);
	
				// Health glow
				const auto entity_health = entity.get_health();
				glow.set(
					1.f - (entity_health / 100.f),	// R
					entity_health / 100.f,			// G
					0.f / 255.f,					// B
					0.8f							// A
				);

				g_memory->write<sdk::structs::glow_object_t>(entity_glow_offset, glow); // Set glow
			}

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}