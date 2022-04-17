#include "pch.hpp"
#include "triggerbot.hpp"

void c_triggerbot::run(keybind& keybd)
{
	log_debug("initializing triggerbot thread.");

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

			c_entity local_player = {};

			const auto max_player_count = sdk::base->get_max_player_count();
			if (max_player_count <= 1)
				continue;

			for (std::int32_t i = 0; i < max_player_count; i++)
			{
				c_entity entity(i);
				if (entity.get_entity())
				{
					const auto crosshair_id = local_player.crosshair_id();
					if (local_player.team() != entity.team())
					{
						if (crosshair_id > 0 && crosshair_id <= 64)
							memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceAttack, 6);
					}
				}
			}

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}