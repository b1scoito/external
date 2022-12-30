#include "pch.hpp"
#include "edgejump.hpp"

void c_edgejump::run() {
	while (var::b_is_running)
	{
		if (!config.misc.b_enable_ej) {
			timer::sleep(1);
			continue;
		}

		if (!var::binds::hold_edgejump_key.get()) {
			timer::sleep(1);
			continue;
		}

		// Check if in a game
		if (!g_engine->in_game())
			continue;

		if (!(g_local.get_flags() & sdk::structs::flags::FL_ONGROUND))
			continue;

		auto vec_origin = g_local.origin();
		auto vec_origin_cpy = vec_origin;

		vec_origin_cpy.z -= 15;

		// Cast a ray trace onto the object
		static rn::valve::trace_t ray = {};
		var::bsp::bp.trace_ray(rn::vector3(vec_origin.x, vec_origin.y, vec_origin.z), 
			rn::vector3(vec_origin_cpy.x, vec_origin_cpy.y, vec_origin_cpy.z), &ray);

		if ( ray.fraction == 1.0f ) {
			g_client->force_jump(6); // +jump
		}
	}
}