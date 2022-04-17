#include "pch.hpp"
#include "glow.hpp"

void c_glow::run(keybind kb)
{
	log_debug("Initializing Glow thread.");

	std::thread([&] {
		while (var::b_is_running)
		{
			if (!kb.get())
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

			const auto glow_obj_manager = memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwGlowObjectManager);
			
			static c_entity local_player = {};
			const auto local_team_id = local_player.team();

			const auto max_player_count = sdk::base->get_max_player_count();
			if (max_player_count <= 1)
				continue;

			for (std::int32_t i = 0; i < max_player_count; i++)
			{
				const auto entity = memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (i * 0x10));
				if (entity)
				{
					const auto entity_life_state = memory->read<std::int32_t>(entity + sdk::netvars::m_lifeState);
					if (!(entity_life_state == sdk::structs::entity_life_state::LIFE_ALIVE))
						continue;

					const auto entity_dormant = memory->read<bool>(entity + sdk::offsets::m_bDormant);
					if (entity_dormant)
						continue;

					const auto entity_glow_index = memory->read<std::int32_t>(entity + sdk::netvars::m_iGlowIndex);
					const auto entity_glow_offset = (glow_obj_manager + (entity_glow_index * 0x38));
					auto glow = memory->read<sdk::structs::glow_object_t>(entity_glow_offset);

					const auto entity_team_id = memory->read<std::int32_t>(entity + sdk::netvars::m_iTeamNum);
					if (local_team_id != entity_team_id)
					{
						glow.set(
							153.f / 255.f, // R
							117.f / 255.f, // G
							255.f / 255.f, // B
							0.7f		   // A
						);

						memory->write<sdk::structs::glow_object_t>(entity_glow_offset, glow); // Set glow
					}
				}
			}

			// Update last frame and last tick
			last_frame = global_vars.iFrameCount;
			last_tick = global_vars.iTickCount;
		}
	}).detach();
}