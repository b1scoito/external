#pragma once

#include "memory.hpp"
#include "sdk.hpp"
#include "structs.hpp"

class c_bhop
{
private:
	int last_tick = {};
	int last_frame = {};

public:
	c_bhop() = default;
	~c_bhop() = default;

	void run();

};

inline auto bhop = std::make_unique<c_bhop>();