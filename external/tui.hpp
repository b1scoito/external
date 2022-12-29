#pragma once

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "weapon.hpp"

using namespace ftxui;

class c_tui
{
public:
	c_tui() = default;
	~c_tui() = default;

	void render();

private:
	Component render_menu();
	Component wrap_menu(std::string name, Component component);
};

inline auto g_tui = std::unique_ptr<c_tui>();