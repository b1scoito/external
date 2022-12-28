#pragma once

#include "archivex.hpp"

#include <shlobj.h>
#include <fstream>
#include <filesystem>

class c_config
{
private:
	std::filesystem::path path;
	std::vector<std::string> configs;

public:
	void run(std::string name);
	void load(size_t id);
	void save(size_t id) const;
	void add(std::string name);
	void remove(size_t id);
	void rename(size_t item, std::string new_name);
	void reset();

	constexpr auto& get_configs() { return configs; };
	constexpr auto& get_path() { return path; };

	struct
	{
		// Aimbot
		bool b_aim_enable = false;
		float f_aim_smooth = 15.f;
		float f_aim_fov = 10.f;

		// Triggerbot
		bool b_trigger_enable = false;
	} aimbot;

	struct
	{
		// Glow
		bool b_glow_enable = false;
		bool b_glow_health = false;

		float f_glow_r = 0.0f;
		float f_glow_g = 0.0f;
		float f_glow_b = 255.0f;
		float f_glow_a = 1.0f;

		// Skin changer
		bool b_sc_enable = false;
		bool b_sc_set_paint_kit = false;
	} visuals;

	struct
	{
		// Bhop
		bool b_enable_bhop = false;

		// EJ
		bool b_enable_ej = false;
	} misc;
};

inline auto config = c_config();