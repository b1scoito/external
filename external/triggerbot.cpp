#include "pch.hpp"
#include "triggerbot.hpp"

void c_triggerbot::run(keybind& keybd)
{
	log_debug(xorstr("initializing triggerbot thread."));

	std::thread([&] {
		while (var::b_is_running)
		{
			if (!keybd.get())
			{
				timer::sleep(50);
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
			if (const auto hwnd = FindWindow(xorstr("Valve001"), nullptr); !(hwnd == GetForegroundWindow()))
				continue;

			// Check if in menu
			if (sdk::base->in_menu())
				continue;

			// Check if in a game
			if (!sdk::base->in_game())
				continue;

			// Localplayer
			const c_entity local_player = {};
			
			const auto crosshair_id = local_player.crosshair_id();
			const c_entity entity(crosshair_id - 1);

			if (!entity.get_entity())
				continue;

			if ((entity.get_team() > sdk::structs::team_id::TEAM_SPECTATOR) && (local_player.get_team() == entity.get_team()))
				continue;

			if (entity.has_immunity())
				continue;

			// thanks bruno for the help
			if (crosshair_id > 0 && crosshair_id <= 64)
				local_player.force_attack(6);

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}