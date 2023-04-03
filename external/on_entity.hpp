#pragma once
#include "pch.hpp"

inline void on_entity_cache()
{
	while (var::b_is_running)
	{
		timer::sleep(250);
	}
}