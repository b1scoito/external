#pragma once

#include "process.hpp"
#include "memory.hpp"
#include "offsets.hpp"
#include "structs.hpp"

#include <fstream>

#include <psapi.h>

class c_basesdk
{
private:
	process proc = {};

	std::pair<std::uintptr_t, std::uintptr_t> engine = {};
	std::pair<std::uintptr_t, std::uintptr_t> client = {};
	std::pair<std::uintptr_t, std::uintptr_t> vstdlib = {};

	struct image_t
	{
		std::uintptr_t base;
		std::uintptr_t size;
	} image = {};

public:
	c_basesdk() = default;
	~c_basesdk();

	bool run();
	const bool check_for_version_mismatch() const;

	constexpr auto& get_engine_image()
	{
		image = { engine.first, engine.second };
		return image;
	};

	constexpr auto& get_client_image()
	{
		image = { client.first, client.second };
		return image;
	};

	constexpr auto& get_vstdlib_image()
	{
		image = { vstdlib.first, vstdlib.second };
		return image;
	};

};

namespace sdk
{
	inline auto base = std::make_unique<c_basesdk>();
}