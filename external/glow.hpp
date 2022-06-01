#pragma once

class c_glow
{
private:
	int last_tick = {};
	int last_frame = {};

	float function_elapsed = {};
	std::mutex mutex = {};

public:
	c_glow() = default;
	~c_glow() = default;

	void run( keybind& keybd );
};

inline auto g_glow = std::make_unique<c_glow>();