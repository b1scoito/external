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
	c_tui() : _screen(ScreenInteractive::Fullscreen()) {};
	~c_tui() = default;

	void render();

	void add_log(std::string line);
private:
	ScreenInteractive _screen;
	std::vector<std::string> log = {};

	Component render_menu();
	Component wrap_menu(std::string name, Component component);
};

inline auto g_tui = std::unique_ptr<c_tui>();