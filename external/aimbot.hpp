#pragma once

class c_aimbot
{
private:
	int last_tick = {};
	int last_frame = {};

	std::vector<sdk::structs::bone_index> bones = {
		sdk::structs::BONE_HEAD,
		sdk::structs::BONE_NECK,
		sdk::structs::BONE_SPINE_0,
		sdk::structs::BONE_SPINE_1,
		sdk::structs::BONE_SPINE_2,
		sdk::structs::BONE_SPINE_3};

	float best_fov = {};
	float smoothing = 1.f;

	Vector best_angle = Vector{};

	float function_elapsed = {};

public:
	c_aimbot() = default;
	~c_aimbot() = default;

	void run(keybind &keybd);
};

inline auto g_aimbot = std::make_unique<c_aimbot>();