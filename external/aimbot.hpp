#pragma once

class c_aimbot
{
private:
	int last_tick = {};
	int last_frame = {};

	float best_fov = 8.f;
	float smoothing = 16.f;
	Vector best_angle = Vector{};

	float function_elapsed = {};

public:
	c_aimbot() = default;
	~c_aimbot() = default;

	void run(keybind& keybd);
};

inline auto g_aimbot = std::make_unique<c_aimbot>();