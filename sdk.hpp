#pragma once

#include "process.hpp"
#include "memory.hpp"
#include "offsets.hpp"
#include "structs.hpp"

class c_basesdk
{
private:
	process proc = {};

	std::pair<std::uintptr_t, std::uintptr_t> engine = {};
	std::pair<std::uintptr_t, std::uintptr_t> client = {};

	struct image_t {
		std::uintptr_t base;
		std::uintptr_t size;
	} image;

public:
	c_basesdk() = default;
	~c_basesdk();

	void run();
	bool in_game();
	bool in_menu();

	std::uintptr_t get_local_player();

	constexpr auto& get_engine_image() { 
		image = { .base = engine.first, .size = engine.second }; 
		return image; 
	};

	constexpr auto& get_client_image() { 
		image = { .base = client.first, .size = client.second };
		return image; 
	};
};

namespace sdk 
{
	inline auto base = std::make_unique<c_basesdk>();
}