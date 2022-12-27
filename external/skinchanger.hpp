#pragma once

class c_skinchanger
{
public:
	c_skinchanger() = default;
	~c_skinchanger() = default;

	void populate_model_index_list();
	std::int32_t find_model_index_by_name(std::string_view model_name);

	void run();
};

inline std::map<std::string, std::int32_t> g_model_index_list = {};
inline auto g_skinchanger = std::make_unique<c_skinchanger>();