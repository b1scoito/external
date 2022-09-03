#include "pch.hpp"
#include "aimbot.hpp"

#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"

void c_aimbot::run(keybind& keybd)
{
	log_debug(xorstr("initializing aimbot thread."));

	std::thread([&]
		{
			while (var::b_is_running)
			{
				if (!keybd.get())
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
				if (!(var::game::wnd == GetForegroundWindow()))
					continue;

				// Check if in menu
				if (g_client->in_menu())
					continue;

				// Check if in a game
				if (!g_engine->in_game())
					continue;

				const auto calculate_angle = [&](Vector local_pos, Vector enemy_pos, Vector view_angles) -> Vector {
					return ((enemy_pos - local_pos).ToAngle() - view_angles);
				};

				for (std::int32_t i = 1; i < g_engine->get_max_player_count(); i++)
				{
					const c_entity entity(g_memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + (i * 0x10)));

					if (!entity.get_entity())
						continue;

					if (entity.get_class_id() != (int)sdk::structs::class_index::CCSPlayer)
						continue;

					if (entity.is_localplayer())
						continue;

					if (!entity.is_alive())
						continue;

					if (entity.is_dormant())
						continue;

					if (!entity.is_enemy())
						continue;

					// Target angle of the enemy
					const auto angle = calculate_angle(g_local.eye_position(), 
						entity.bone_matrix(sdk::structs::BONE_HEAD), (g_engine->get_view_angles() + (g_local.aim_punch() * 2)));

					const auto fov = std::hypot(angle.x, angle.y);

					//log_debug("fov: %.3f angle: x: %.3f, y: %.3f, z: %.3f", fov, angle.x, angle.y, angle.z);

					if (fov < this->best_fov) {
						this->best_fov = fov;
						this->best_angle = angle;
					}

					//log_debug("best fov: %.3f best angle: x: %.3f, y: %.3f, z: %.3f", this->best_fov, this->best_angle.x, this->best_angle.y, this->best_angle.z);
				}

				if (!best_angle.IsZero())
					g_engine->set_view_angles((g_engine->get_view_angles() + this->best_angle) / this->smoothing);



				const auto end = std::chrono::high_resolution_clock::now();

				// Update last frame and last tick
				last_tick = global_vars.iTickCount;
				last_frame = global_vars.iFrameCount;

				std::chrono::duration<float, std::milli> elapsed = end - start;
				function_elapsed = elapsed.count();
			}
		}).detach();
}