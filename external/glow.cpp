#include "pch.hpp"
#include "glow.hpp"

void c_glow::run(keybind& keybd)
{
	log_debug("initializing glow thread.");

	std::thread([&] {
		while (var::b_is_running)
		{
			if (!keybd.get())
			{
				std::this_thread::sleep_for(50ms);
				continue;
			}

			// Only update each tick
			const auto global_vars = world->get_globalvars();

			const auto update = (global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame);
			// Sleep for performance
			if (!update) // Why does this have to make sense?
				timer::sleep(1.f);
			else
				timer::sleep(1.f);

			// Check if active window is CS:GO
			if (const auto hwnd = FindWindow(L"Valve001", nullptr); !(hwnd == GetForegroundWindow()))
				continue;

			// Check if in menu
			if (sdk::base->in_menu())
				continue;

			// Check if in a game
			if (!sdk::base->in_game())
				continue;
			
			// Local player
			c_entity local_player = {};

			const auto max_player_count = sdk::base->get_max_player_count();
			for (std::int32_t i = 0; i < max_player_count; i++)
			{
				c_entity entity(i);

				if (!entity.get_entity())
					continue;

				if (entity.is_localplayer())
					continue;

				if (!entity.is_alive())
					continue;

				if (entity.is_dormant())
					continue;

				if (local_player.team() == entity.team())
					continue;

				const auto glow_obj_manager = memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwGlowObjectManager);
				const auto entity_glow_offset = glow_obj_manager + (entity.glow_index() * 0x38);

				auto glow = memory->read<sdk::structs::glow_object_t>(entity_glow_offset);

				glow.set(
					153.f / 255.f, // R
					117.f / 255.f, // G
					255.f / 255.f, // B
					0.6f		   // A
				);

				memory->write<sdk::structs::glow_object_t>(entity_glow_offset, glow); // Set glow
			}

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}