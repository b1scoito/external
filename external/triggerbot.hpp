#pragma once

// SDK
#include "memory.hpp"
#include "sdk.hpp"
#include "structs.hpp"

// Classes
#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"

class c_triggerbot
{
private:
	int last_tick = {};
	int last_frame = {};

public:
	c_triggerbot() = default;
	~c_triggerbot() = default;

	void run( keybind &keybd );
};

inline auto triggerbot = std::make_unique<c_triggerbot>();