#pragma once

namespace var
{
	namespace game {
		inline std::wstring str_process = L"csgo.exe";
	}

	namespace keybinds {
		inline auto toggle_glow_keybind = keybind(true, keybind_state_t::toggle, VK_HOME);
	}

	inline bool b_is_running = true;
}