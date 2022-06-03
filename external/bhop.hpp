#pragma once

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

inline auto g_bhop = std::make_unique<c_bhop>();