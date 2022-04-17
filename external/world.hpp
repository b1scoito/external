#pragma once

class c_world
{
private:

public:
	const auto get_globalvars() const
	{
		return memory->read<sdk::structs::globalvars_t>(sdk::base->get_engine_image().base + sdk::offsets::dwGlobalVars);
	}
};

inline auto world = std::make_unique<c_world>();