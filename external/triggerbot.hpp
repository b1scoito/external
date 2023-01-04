#pragma once

#include "engine.hpp"
#include "client.hpp"

class c_triggerbot
{
private:
	int last_tick = {};
	int last_frame = {};

	float function_elapsed = {};

public:
	c_triggerbot() = default;
	~c_triggerbot() = default;

	void run();
};

inline auto g_triggerbot = std::make_unique<c_triggerbot>();