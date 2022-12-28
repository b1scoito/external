#pragma once

class c_weapon
{
private:
	std::int32_t index = {};

public:
	c_weapon(const std::int32_t e_index = {})
	{
		this->index = e_index;
	}

public: // Read
	constexpr auto& get_weapon_index() const
	{
		return this->index;
	}

	const bool is_sniper() const;
	const bool is_pistol() const;
	const bool is_knife() const;
	const bool is_grenade() const;
};