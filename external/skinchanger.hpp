#pragma once

// SDK
#include "memory.hpp"
#include "sdk.hpp"
#include "structs.hpp"

// Classes
#include "world.hpp"
#include "entity.hpp"

class c_skinchanger
{
private:
	int last_tick = {};
	int last_frame = {};

public:
	c_skinchanger() = default;
	~c_skinchanger() = default;

	void run();
};

inline auto skinchanger = std::make_unique<c_skinchanger>();