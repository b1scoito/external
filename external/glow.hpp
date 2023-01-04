#pragma once

#include "engine.hpp"
#include "client.hpp"

class c_glow
{
private:
	int last_tick = {};
	int last_frame = {};

	float function_elapsed = {};

public:
	c_glow() = default;
	~c_glow() = default;

	void run();
};

inline auto g_glow = std::make_unique<c_glow>();