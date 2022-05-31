#pragma once

class c_triggerbot
{
private:
	int last_tick = {};
	int last_frame = {};

	float function_elapsed = {};

public:
	c_triggerbot() = default;
	~c_triggerbot() = default;

	void run( keybind& keybd );
};

inline auto triggerbot = std::make_unique<c_triggerbot>();