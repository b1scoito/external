#pragma once

#include "memory.hpp"
#include "sdk.hpp"
#include "structs.hpp"

class c_glow
{
private:
	int last_tick = {};
	int last_frame = {};

public:
	c_glow() = default;
	~c_glow() = default;

	void run();
};

inline auto glow = std::make_unique<c_glow>();