#include "pch.hpp"

#include "bhop.hpp"
#include "glow.hpp"
#include "triggerbot.hpp"
#include "skinchanger.hpp"
#include "aimbot.hpp"

#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"
#include "weapon.hpp"
#include "convar.hpp"

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

Component render_menu(sdk::structs::globalvars_t& globals) {
	return Renderer([&] {
		return hbox({
			text("external"),
			separatorHeavy(),
			text("glow") | color(Color::RGB((uint8_t)config.visuals.f_glow_r, (uint8_t)config.visuals.f_glow_g, (uint8_t)config.visuals.f_glow_b)),
		}) | xflex | border;
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
			timer::sleep(1000);

			// Cache
			if (!g_engine->in_game())
			{
				g_local = c_entity();
				g_convar_list.clear();
				g_model_index_list.clear();
				continue;
			}

			std::string map = g_engine->get_map_name();
			static std::string current_map = "";
			if (map != current_map)
			{
				current_map = map;
				var::bsp::parsed_map = var::bsp::bp.load_map(g_engine->get_game_directory(), g_engine->get_map_name());
				if (!var::bsp::parsed_map)
					std::cerr << "Failed to load map into BSP parser!\n";
			}

			if (!g_local.get_entity())
			{
				const auto [addr, index] = g_client->get_local_player();
				g_local = c_entity(addr, index);
			}

			if (g_convar_list.empty())
				g_convar->populate_convars();

			if (g_model_index_list.empty())
				g_skinchanger->populate_models();
		} 
	}).detach();

	// Run config system
	config.run("external");

	// Run bhop
	g_bhop->run();

	// Run glow
	g_glow->run();

	// Run trigger bot
	g_triggerbot->run(var::binds::hold_triggerbot_key);

	// Run skin changer
	g_skinchanger->run();

	// Run aimbot
	g_aimbot->run(var::binds::hold_aimbot_key);

	std::thread([&] {
		auto screen = ScreenInteractive::Fullscreen();

		auto global_vars = g_engine->get_globalvars();
		const auto menu = render_menu(global_vars);

		// Aimbot
		const auto aimbot_menu = wrap_menu("aimbot", Container::Vertical({
			Checkbox("enable", &config.aimbot.b_aim_enable),
			Slider("smooth: ", &config.aimbot.f_aim_smooth, 1.f, 360.f, 1.f),
			Slider("   fov: ", &config.aimbot.f_aim_fov, 1.f, 180.f, 1.f),
		}));

		// Bhop
		const auto bhop_menu = wrap_menu("bhop", Container::Vertical({
			Checkbox("enable", &config.misc.b_enable_bhop),
		}));

		// Bhop
		const auto edgejump_menu = wrap_menu("edge jump", Container::Vertical({
			Checkbox("enable", &config.misc.b_enable_ej),
		}));

		// Glow
		const auto glow_menu = wrap_menu("glow", Container::Vertical({
			Checkbox("enable", &config.visuals.b_glow_enable),
			Checkbox("health based", &config.visuals.b_glow_health_based),
			Container::Horizontal({
				Slider(" r: ", &config.visuals.f_glow_r, 1.0f, 255.f, 1.f),
				Slider(" g: ", &config.visuals.f_glow_g, 1.0f, 255.f, 1.f),
				Slider(" b: ", &config.visuals.f_glow_b, 1.0f, 255.f, 1.f),
				Slider(" a: ", &config.visuals.f_glow_a, 0.f, 1.f, 0.1f),
			}),
		}));

		for (const auto& [weapon_id, weapon_info] : sdk::structs::item_list)
		{
			if (c_weapon(weapon_id).is_knife())
				var::skins::models.push_back(weapon_info.name);
		}

		// Skin changer
		const auto skinchanger_menu = wrap_menu("skin changer", Container::Vertical({
			Checkbox("enable", &config.visuals.b_sc_enable),
			Checkbox("set paint kit", &config.visuals.b_sc_set_paint_kit),
			Container::Horizontal({
				Dropdown(&var::skins::models, &config.visuals.i_selected_model_index),
			}),
		}));

		// Trigger bot
		const auto triggerbot_menu = wrap_menu("trigger", Container::Vertical({
			Checkbox("enable", &config.aimbot.b_trigger_enable),
		}));

		// Config
		const auto config_menu = wrap_menu("config", Container::Vertical({
			Container::Horizontal({
				Button("save", [&] {
					config.add("config");
					config.save(0);
				}, ButtonOption::Animated()) | flex_shrink,

				Button("load", [&] {
					config.load(0);
				}, ButtonOption::Animated()) | flex_shrink,

			}),
		}));

		std::vector<std::string> tab_values
		{
			"Aimbot ",
			"Visuals ",
			"Misc ",
			"Players ",
			"Config "
		};

		// Layout
		// Aimbot tab
		const auto aimbot_tab = Container::Vertical({
			aimbot_menu,
			triggerbot_menu,
		}) | flex;

		// Visuals tab
		const auto visuals_tab = Container::Vertical({
			glow_menu,
			skinchanger_menu,
		}) | flex;

		// Misc tab
		const auto misc_tab = Container::Vertical({
			bhop_menu,
			edgejump_menu,
		}) | flex;

		// Players tab
		const auto players_tab = Container::Vertical({

		}) | flex;

		// Config tab
		const auto config_tab = Container::Vertical({
			config_menu,
		}) | flex;

		int tab_selected = {};

		auto tab_menu = Menu(&tab_values, &tab_selected);
		auto tab_container = Container::Tab(
		{
			aimbot_tab,
			visuals_tab,
			misc_tab,
			players_tab,
			config_tab
		}, &tab_selected);

		auto container = Container::Horizontal({
			tab_menu,
			tab_container,
		});

		const auto component = Renderer(container, [&] {
			return vbox({
				menu->Render(),
				separatorHeavy() | dim,
				hbox({
					tab_menu->Render(),
					separator(),
					tab_container->Render(),
				}) | flex | border,
			});
		});

		screen.Loop(component);
	}).detach();

	while (!LI_FN(GetAsyncKeyState).cached()(VK_DELETE))
		timer::sleep(50);

	var::b_is_running = false;

	return EXIT_SUCCESS;
}