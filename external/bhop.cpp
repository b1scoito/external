#include "pch.hpp"
#include "bhop.hpp"

void c_bhop::run()
{
	log_debug("initializing bhop thread.");

	std::thread([&] {
		while (var::b_is_running)
		{
			// Only update each tick
			const auto global_vars = world->get_globalvars();

			const auto update = ( global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame );
			// Sleep for performance
			if (!update) // Why does this have to make sense?
				timer::sleep(1.f);
			else
				timer::sleep(1.f);

			// Check if active window is CS:GO
			if (const auto hwnd = FindWindow(L"Valve001", nullptr); !(hwnd == GetForegroundWindow()))
				continue;

			// Check if space is pressed down
			if (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
				continue;

			// Check if in menu
			if (sdk::base->in_menu())
				continue;

			// Check if in a game
			if (!sdk::base->in_game())
				continue;

			// Check if in ladder, noclip or observer
			static c_entity local_player = {};
			const auto move_type = local_player.move_type();
			if (move_type == sdk::structs::entity_move_type::MOVETYPE_LADDER || move_type == sdk::structs::entity_move_type::MOVETYPE_NOCLIP || move_type == sdk::structs::entity_move_type::MOVETYPE_OBSERVER)
				continue;

			// Check if onground and jump, otherwise, set jumped to false
			if ((local_player.flags() & sdk::structs::entity_flags::FL_ONGROUND))
				memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceJump, 5); // +jump
			else
				memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceJump, 4); // -jump
			
			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}