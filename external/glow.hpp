#pragma once

// SDK
#include "memory.hpp"
#include "sdk.hpp"
#include "structs.hpp"

// Classes
#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"

class c_glow
{
private:
	int last_tick = {};
	int last_frame = {};

	float function_elapsed = {};

public:
	c_glow() = default;
	~c_glow() = default;

	void run( keybind& keybd );
};

inline auto glow = std::make_unique<c_glow>();