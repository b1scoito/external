#include "pch.hpp"
#include "bhop.hpp"

void c_bhop::run()
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

			// Check if space is pressed down
			if (!(GetAsyncKeyState(VK_SPACE) & 0x8000))
				continue;

			const auto global_vars = g_mem->read<sdk::structs::globalvars_t>(sdkbase->enginebase + sdk::offsets::dwGlobalVars);

			// Only update each tick
			auto update = ( global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame );
			if (!update)
				continue;

			// Check if in a game
			if (!sdkbase->in_game())
				continue;

			// Check if in menu
			if (sdkbase->in_menu())
				continue;

			// Check if in ladder, noclip or observer
			const auto m_MoveType = g_mem->read<std::uint8_t>(sdkbase->local_player + sdk::netvars::m_MoveType);
			if (m_MoveType == sdk::structs::entity_move_type::MOVETYPE_LADDER 
				|| m_MoveType == sdk::structs::entity_move_type::MOVETYPE_NOCLIP 
				|| m_MoveType == sdk::structs::entity_move_type::MOVETYPE_OBSERVER)
				continue;

			// Check if onground and jump, otherwise, set jumped to false
			const auto m_fFlags = g_mem->read<std::uint8_t>(sdkbase->local_player + sdk::netvars::m_fFlags);
			if ((m_fFlags & sdk::structs::entity_flags::FL_ONGROUND))
				g_mem->write<std::int32_t>(sdkbase->clientbase + sdk::offsets::dwForceJump, 5);
			else
				g_mem->write<std::int32_t>(sdkbase->clientbase + sdk::offsets::dwForceJump, 4);

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).join();
}