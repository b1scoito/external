#pragma once

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "weapon.hpp"

using namespace ftxui;
inline std::vector<std::string> event_log;

class c_tui
{
private:	
	Component render_menu();
	Component wrap_menu(std::string name, Component component);

public:
	c_tui() = default;
	~c_tui() = default;

	void render();
	void append_log(std::string_view msg);
};

inline auto g_tui = std::unique_ptr<c_tui>();