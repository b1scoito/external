#include "pch.hpp"
#include "bhop.hpp"

void c_bhop::run()
{
	log_debug("starting bhop thread");

	std::thread([&] {
		while (var::b_is_running)
		{
			// Sleep for performance
			timer::sleep(1.f);

			// Only update each tick
			const auto global_vars = g_mem->read<sdk::structs::globalvars_t>(sdk::base->get_engine_image().base + sdk::offsets::dwGlobalVars);
			const auto update = ( global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame );
			if (!update)
				continue;

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
			const auto m_MoveType = g_mem->read<std::uint8_t>(sdk::base->get_local_player() + sdk::netvars::m_MoveType);
			if (m_MoveType == sdk::structs::entity_move_type::MOVETYPE_LADDER || m_MoveType == sdk::structs::entity_move_type::MOVETYPE_NOCLIP || m_MoveType == sdk::structs::entity_move_type::MOVETYPE_OBSERVER)
				continue;

			// Check if onground and jump, otherwise, set jumped to false
			const auto m_fFlags = g_mem->read<std::uint8_t>(sdk::base->get_local_player() + sdk::netvars::m_fFlags);
			if ((m_fFlags & sdk::structs::entity_flags::FL_ONGROUND))
				g_mem->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceJump, 5); // +jump
			else
				g_mem->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceJump, 4); // -jump
			
			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}