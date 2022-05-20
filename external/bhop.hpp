#pragma once

// SDK
#include "memory.hpp"
#include "sdk.hpp"
#include "structs.hpp"

// Classes
#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"

class c_bhop
{
private:
	int last_tick = {};
	int last_frame = {};

	float function_elapsed = {};

public:
	c_bhop() = default;
	~c_bhop() = default;

	void run();
};

inline auto bhop = std::make_unique<c_bhop>();