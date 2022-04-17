#include "pch.hpp"
#include "glow.hpp"

void c_glow::run()
{
	log_debug("initializing");

	std::thread([&] {
		while (var::b_is_running)
		{
			// Sleep for performance
			timer::sleep(1.f);

			// Check if active window is CS:GO
			if (const auto hwnd = FindWindow(L"Valve001", nullptr); !(hwnd == GetForegroundWindow()))
				continue;

			const auto global_vars = g_mem->read<sdk::structs::globalvars_t>(sdkbase->enginebase + sdk::offsets::dwGlobalVars);

			// Only update each tick
			auto update = (global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame);
			if (!update)
				continue;

			// Check if in a game
			if (!sdkbase->in_game())
				continue;

			// Check if in menu
			if (sdkbase->in_menu())
				continue;

			log_debug("coiso");

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
		}).join();
}