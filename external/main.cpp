#include "pch.hpp"

#include "bhop.hpp"
#include "glow.hpp"
#include "triggerbot.hpp"
#include "skinchanger.hpp"
#include "aimbot.hpp"

#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"
#include "convar.hpp"

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

Component render_menu() {
	return Renderer([] {
		return vbox({
			text("external v1.0") | border | flex,
		}) | xflex;
	});
}

Component wrap_menu(std::string name, Component component) {
	return Renderer(component, [name, component] {
		return vbox({
			hbox({
				separator(),
				text(name) | bold | dim,
				separator()
			}),
			separator(),
			component->Render() | xflex,
			separator(),
		}) | xflex;
	});
}

int main(int argc, const char *argv[])
{
	std::atexit([]
		{ var::b_is_running = false; });

	// Run SDK
	if (!sdk::base->run())
		return EXIT_FAILURE;

	// Update thread
	std::thread([&] {
		while (var::b_is_running)
		{
			timer::sleep(100);

			// Cache
			if (!g_engine->in_game())
			{
				g_local = c_entity();
				g_convar_list.clear();
				g_model_index_list.clear();
				continue;
			}

			if (!g_local.get_entity())
			{
				const auto [addr, index] = g_client->get_local_player();
				g_local = c_entity(addr, index);
			}

			if (g_convar_list.empty())
				g_convar->populate_list();

			if (g_model_index_list.empty())
				g_skinchanger->populate_model_index_list();
		} 
	}).detach();

	// Run bhop
	g_bhop->run();

	// Run glow
	g_glow->run();

	// Run trigger bot
	g_triggerbot->run(var::keybinds::hold_triggerbot_key);

	// Run skin changer
	g_skinchanger->run();

	// Run aimbot
	g_aimbot->run(var::keybinds::hold_aimbot_key);

	std::thread([&] {
		auto screen = ScreenInteractive::Fullscreen();

		auto aimbot = Container::Vertical({
			Checkbox("Enable", &var::cheats::aimbot::enable),
			Slider("Smooth: ", &var::cheats::aimbot::smooth, 1.f, 360.f, 1.f),
			Slider("   FOV: ", &var::cheats::aimbot::fov, 1.f, 180.f, 1.f),
		});

		auto bhop = Container::Vertical({
			Checkbox("Enable", &var::cheats::bhop::enable),
		});

		auto glow = Container::Vertical({
			Checkbox("Enable", &var::cheats::glow::enable),
			Checkbox("Health Glow", &var::cheats::glow::enable_health_glow),
			Container::Horizontal({
				Slider("R: ", &var::cheats::glow::red_color, 1.0f, 255.f, 1.f),
				Slider("G: ", &var::cheats::glow::green_color, 1.0f, 255.f, 1.f),
				Slider("B: ", &var::cheats::glow::blue_color, 1.0f, 255.f, 1.f),
				Slider("A: ", &var::cheats::glow::alpha_color, 0.f, 1.f, 0.1f),
			}),
		});

		auto skinchanger = Container::Vertical({
			Checkbox("Enable", &var::cheats::skinchanger::enable),
			Checkbox("Set Skin", &var::cheats::skinchanger::set_skins),
		});

		auto triggerbot = Container::Vertical({
			Checkbox("Enable", &var::cheats::triggerbot::enable),
		});

		const auto menu = render_menu();
		aimbot = wrap_menu("Aimbot", aimbot);
		bhop = wrap_menu("Bhop", bhop);
		glow = wrap_menu("Glow", glow);
		skinchanger = wrap_menu("Skin changer", skinchanger);
		triggerbot = wrap_menu("Trigger", triggerbot);


		// Layout
		auto layout = Container::Vertical({
			menu,
			aimbot,
			bhop,
			glow,
			skinchanger,
			triggerbot,
		});

		auto component = Renderer(layout, [&] {
			return vbox({
				menu->Render(),
				separatorHeavy() | dim,
				vbox({
					aimbot->Render(),
					bhop->Render(),
					glow->Render(),
					skinchanger->Render(),
					triggerbot->Render(),
				}) | xflex | border
			});
		});

		screen.Loop(component);
	}).detach();

	while (!LI_FN(GetAsyncKeyState).cached()(VK_DELETE))
		timer::sleep(50);

	var::b_is_running = false;

	return EXIT_SUCCESS;
}