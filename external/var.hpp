#pragma once

namespace var
{
	namespace cheats {
		namespace aimbot {
			inline bool enable = false;
			inline float smooth = 180.f;
			inline float fov = 10.f;
		}

		namespace bhop {
			inline bool enable = false;
		}

		namespace glow {
			inline bool enable = false;
			inline bool enable_health_glow = false;

			inline float red_color = 0.0f;
			inline float green_color = 0.0f;
			inline float blue_color = 255.0f;
			inline float alpha_color = 1.0f;
		}

		namespace skinchanger
		{
			inline bool enable = false;
			inline bool set_skins = false;
		}

		namespace triggerbot {
			inline bool enable = false;
		}
	}

	namespace game
	{
		inline std::wstring str_process = xorstr(L"csgo.exe");
		inline HWND wnd = {};
	}

	namespace keybinds
	{
		inline auto hold_triggerbot_key = keybind(false, keybind_state_t::hold, VK_XBUTTON2);
		inline auto hold_aimbot_key = keybind(false, keybind_state_t::hold, VK_LBUTTON);
	}

	inline bool b_is_running = true;
}