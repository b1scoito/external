#pragma once

namespace var
{
	namespace game
	{
		inline std::wstring str_process = xorstr( L"csgo.exe" );
		inline HWND wnd = {};
		inline std::string current_game_version = xorstr( "1463" );
	}

	namespace keybinds
	{
		inline auto toggle_glow_key = keybind( true, keybind_state_t::toggle, VK_HOME );
		inline auto hold_triggerbot_key = keybind( false, keybind_state_t::hold, VK_XBUTTON2 );
	}

	inline bool b_is_running = true;
}