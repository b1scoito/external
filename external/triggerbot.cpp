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
			if (const auto hwnd = FindWindow(xorstr(L"Valve001"), nullptr); !(hwnd == GetForegroundWindow()))
				continue;

			// Check if in menu
			if (sdk::base->in_menu())
				continue;

			// Check if in a game
			if (!sdk::base->in_game())
				continue;

			// Localplayer
			const c_entity localplayer = {};
			
			const auto crosshair_id = localplayer.crosshair_id();
			const c_entity entity(crosshair_id - 1);

			if (!entity.get_entity())
				continue;

			if ((entity.get_team() > sdk::structs::team_id::TEAM_SPECTATOR) && (localplayer.get_team() == entity.get_team()))
				continue;

			if (entity.has_immunity())
				continue;

			const auto attack = [&]() {
				localplayer.force_attack(5); // +attack
				timer::sleep(5);
				localplayer.force_attack(4); // -attack
			};

			// thanks bruno for the help
			if (crosshair_id > 0 && crosshair_id <= 64)
				attack();

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}