#pragma once

#include "process.hpp"
#include "memory.hpp"
#include "offsets.hpp"

class c_sdkbase
{
private:
	process proc = {};

	std::pair<std::uintptr_t, std::uintptr_t> engine = {};
	std::pair<std::uintptr_t, std::uintptr_t> client = {};

public:
	c_sdkbase() = default;
	~c_sdkbase();

	void run();
	bool in_game();
	bool in_menu();

	std::uintptr_t enginebase = {};
	std::uintptr_t clientbase = {};

	std::uintptr_t local_player = {};
};

inline auto sdkbase = std::make_unique<c_sdkbase>();