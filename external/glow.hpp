#pragma once

// SDK
#include "memory.hpp"
#include "sdk.hpp"
#include "structs.hpp"

// Classes
#include "entity.hpp"
#include "world.hpp"

class c_glow
{
private:
	int last_tick = {};
	int last_frame = {};

public:
	c_glow() = default;
	~c_glow() = default;

	void run(keybind kb);
};

inline auto glow = std::make_unique<c_glow>();