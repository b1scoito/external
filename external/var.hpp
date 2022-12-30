#pragma once

#include "safe_vector.hpp" // for safe_vector
#include "entity.hpp" // for c_entity

namespace var
{
	namespace cs
	{
		inline std::wstring str_process = xorstr(L"csgo.exe");
		inline HWND h_wnd = {};
	}

	namespace binds
	{
		inline auto hold_triggerbot_key = keybind(false, keybind_state_t::hold, VK_XBUTTON2);
		inline auto hold_edgejump_key = keybind(false, keybind_state_t::hold, VK_XBUTTON1);
		inline auto hold_aimbot_key = keybind(false, keybind_state_t::hold, VK_LBUTTON);
	}

	namespace bsp
	{
		inline bool parsed_map = {};
		inline rn::bsp_parser bp = {};
	}

	namespace skins
	{
		inline std::string str_paint_kit = {};
		inline std::vector<std::string> models = {};
	}

	namespace cache {
		inline safe_vector<c_entity> cached_entities = {};
	}

	inline std::atomic<bool> b_is_running = true;
}