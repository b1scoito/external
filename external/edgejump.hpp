#pragma once

#include "engine.hpp"
#include "client.hpp"

class c_edgejump
{
public:
	c_edgejump() = default;
	~c_edgejump() = default;

	void run();
};

inline auto g_edgejump = std::unique_ptr<c_edgejump>();