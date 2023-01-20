#pragma once

#include "engine.hpp"
#include "client.hpp"

class c_aimbot
{
private:
	int last_tick = {};
	int last_frame = {};
	
	float best_fov = {};
	float best_fov_local = { config.aimbot.f_aim_fov };
	Vector best_angle = Vector{};

	float function_elapsed = {};

public:
	c_aimbot() = default;
	~c_aimbot() = default;

	void run();
};

inline auto g_aimbot = std::make_unique<c_aimbot>();