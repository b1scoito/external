#include "pch.hpp"
#include "glow.hpp"

void c_glow::run()
{
	log_debug("starting glow thread");

	std::thread([&] {
		while (var::b_is_running)
		{
			// Sleep for performance
			timer::sleep(1.f);

			// Only update each tick
			const auto global_vars = g_mem->read<sdk::structs::globalvars_t>(sdk::base->get_engine_image().base + sdk::offsets::dwGlobalVars);
			const auto update = (global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame);
			if (!update)
				continue;

			// Check if active window is CS:GO
			if (const auto hwnd = FindWindow(L"Valve001", nullptr); !(hwnd == GetForegroundWindow()))
				continue;

			// Check if in menu
			if (sdk::base->in_menu())
				continue;

			// Check if in a game
			if (!sdk::base->in_game())
				continue;

			const auto glow_obj_manager = g_mem->read<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwGlowObjectManager);

			for (size_t i = 1; i < 32; i++)
			{
				const auto entity = g_mem->read<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + i * 0x10);

				if (entity)
				{
					const auto entity_team_id = g_mem->read<std::int32_t>(entity + sdk::netvars::m_iTeamNum);
					const auto entity_glow = g_mem->read<std::int32_t>(entity + sdk::netvars::m_iGlowIndex);

					if (entity_team_id == sdk::structs::entity_team_id::TEAM_TT) 
					{
						g_mem->write<float>(glow_obj_manager + entity_glow * 0x38 + 0x8, 1.238f); // R
						g_mem->write<float>(glow_obj_manager + entity_glow * 0x38 + 0xC, 190.f); // G
						g_mem->write<float>(glow_obj_manager + entity_glow * 0x38 + 0x10, 255.f); // B
						g_mem->write<float>(glow_obj_manager + entity_glow * 0x38 + 0x14, 255.f); // A

						g_mem->write<bool>(glow_obj_manager + entity_glow * 0x38 + 0x28, true); // Enable glow
					}
					else if (entity_team_id == sdk::structs::entity_team_id::TEAM_CT)
					{
						g_mem->write<float>(glow_obj_manager + entity_glow * 0x38 + 0x8, 255.f); // R
						g_mem->write<float>(glow_obj_manager + entity_glow * 0x38 + 0xC, 200.f); // G
						g_mem->write<float>(glow_obj_manager + entity_glow * 0x38 + 0x10, 142.f); // B
						g_mem->write<float>(glow_obj_manager + entity_glow * 0x38 + 0x14, 255.f); // A

						g_mem->write<bool>(glow_obj_manager + entity_glow * 0x38 + 0x28, true); // Enable glow
					}
				}
			}

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}