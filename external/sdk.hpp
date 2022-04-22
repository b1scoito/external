#pragma once

#include "process.hpp"
#include "memory.hpp"
#include "offsets.hpp"
#include "structs.hpp"

class c_basesdk
{
private:
	std::pair<std::uintptr_t, std::uintptr_t> engine = {};
	std::pair<std::uintptr_t, std::uintptr_t> client = {};

	struct image_t {
		std::uintptr_t base;
		std::uintptr_t size;
	} image = {};

public:
	c_basesdk() = default;
	~c_basesdk();

	void run();
	const std::uintptr_t get_local_player();
	const bool in_game();
	const std::int32_t get_max_player_count();

	const bool in_menu() const;
	const std::int32_t get_game_type() const;
	const std::uintptr_t get_glow_object_manager() const;


	constexpr auto& get_engine_image() { 
		image = { engine.first, engine.second }; 
		return image; 
	};

	constexpr auto& get_client_image() { 
		image = { client.first, client.second };
		return image; 
	};
};

namespace sdk 
{
	inline auto base = std::make_unique<c_basesdk>();
}