#pragma once

// From: https://www.unknowncheats.me/forum/counterstrike-global-offensive/181308-external-convarfinder.html
class c_convar_manager
{
private:
	std::uintptr_t cvar_address = {};

public:
	c_convar_manager(const std::uintptr_t cvar = {})
	{
		this->cvar_address = cvar;
	};

	~c_convar_manager() = default;

public: // Read
	constexpr auto &get_pointer() const
	{
		return this->cvar_address;
	}

	const int get_flags() const;
	const std::string get_default_value() const;
	const std::string get_string() const;
	const float get_float() const;
	const std::int32_t get_int() const;

public: // Write
	const void set(std::string value) const;
	const void set(float value) const;
	const void set(std::int32_t value) const;
};

class c_convar : private c_convar_manager
{
public: // Read
	void populate_list();
	c_convar_manager find(std::string_view convar_name);
};

inline std::map<std::string, std::uintptr_t> g_convar_list = {};
inline auto g_convar = std::make_unique<c_convar>();