#include "pch.hpp"
#include "aimbot.hpp"

void c_aimbot::run()
{
	while (var::b_is_running)
	{
		if (!config.aimbot.b_aim_enable) {
			timer::sleep(1);
			continue;
		}

		if (!var::binds::hold_aimbot_key.get())
		{
			timer::sleep(1);
			continue;
		}

		// Only update each tick
		const auto global_vars = g_engine->get_globalvars();
		const auto update = (global_vars.iTickCount != last_tick || global_vars.iFrameCount != last_frame);
		if (!update)
		{
			timer::sleep(global_vars.flIntervalPerTick);
			continue;
		}

		const auto frametime = global_vars.flAbsFrameTime;
		const auto delay = (function_elapsed - (frametime < global_vars.flIntervalPerTick ? (frametime * 0.5f) : frametime));
		const auto sleep = std::min(delay, (frametime * 1000));

		timer::sleep(sleep);

		const auto start = std::chrono::high_resolution_clock::now();

		// Check if active window is CS:GO
		if (!(var::cs::h_wnd == GetForegroundWindow()))
			continue;

		// Check if in menu
		if (g_client->in_menu())
			continue;

		// Check if in a game
		if (!g_engine->in_game())
			continue;

		const auto calculate_angle = [&](Vector local_pos, Vector enemy_pos, Vector view_angles) -> Vector {
			return ((enemy_pos - local_pos) - view_angles);
		};

		this->best_fov_local = {};
		this->best_angle = Vector{};

		for (std::int32_t i = 1; i < g_engine->get_max_player_count(); i++)
		{
			const c_entity entity(g_memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (i * 0x10)), i);

			if (!entity.get_entity())
				continue;

			if (entity.get_class_id() != (int)sdk::structs::e_class_index::CCSPlayer)
				continue;

			if (entity.is_localplayer())
				continue;

			if (!entity.is_alive())
				continue;

			if (entity.is_dormant())
				continue;

			if (!entity.is_enemy())
				continue;
					
			if (!entity.is_visible_ray())
				continue;

			const auto bone_matrix = entity.bone_matrix(sdk::structs::BONE_HEAD);

			// Target angle of the enemy
			const auto angle = calculate_angle(g_local.eye_pos(), bone_matrix, g_engine->get_view_angles());
			const auto fov = std::hypot(angle.x, angle.y);

			if (fov < best_fov_local) {
				best_fov_local = fov;
				best_angle = angle;
			}

			if (!best_angle.IsZero())
				g_engine->set_view_angles(g_engine->get_view_angles() + best_angle / config.aimbot.f_aim_smooth);
		}

		const auto end = std::chrono::high_resolution_clock::now();

		// Update last frame and last tick
		last_tick = global_vars.iTickCount;
		last_frame = global_vars.iFrameCount;

		std::chrono::duration<float, std::milli> elapsed = end - start;
		function_elapsed = elapsed.count();
	}
}