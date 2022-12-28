#pragma once

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
		inline auto hold_aimbot_key = keybind(false, keybind_state_t::hold, VK_LBUTTON);
	}

	namespace bsp
	{
		inline bool parsed_map = {};
		inline rn::bsp_parser bp = {};
	}

	inline bool b_is_running = true;
}