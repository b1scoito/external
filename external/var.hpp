#pragma once

namespace var
{
	namespace game
	{
		inline std::wstring str_process = xorstr( L"csgo.exe" );
		inline HWND wnd = {};
	}

	namespace keybinds
	{
		inline auto toggle_glow_key = keybind( true, keybind_state_t::toggle, VK_HOME );
		inline auto toggle_skinchanger_key = keybind( false, keybind_state_t::toggle, VK_END );
		inline auto hold_triggerbot_key = keybind( false, keybind_state_t::hold, VK_XBUTTON2 );
		inline auto hold_aimbot_key = keybind( false, keybind_state_t::hold, VK_LBUTTON );
	}

	inline bool b_is_running = true;
}