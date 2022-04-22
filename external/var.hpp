#pragma once

namespace var
{
	namespace game {
		inline std::string str_process = xorstr("csgo.exe");
	}

	namespace keybinds {
		inline auto toggle_glow_key = keybind(true, keybind_state_t::toggle, VK_HOME);
		inline auto hold_triggerbot_key = keybind(false, keybind_state_t::hold, VK_XBUTTON2);
	}

	inline bool b_is_running = true;
}