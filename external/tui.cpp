#include "pch.hpp"
#include "tui.hpp"

void c_tui::render() 
{
	auto screen = ScreenInteractive::Fullscreen();

	// Aimbot
	const auto aimbot_menu = wrap_menu(" - aimbot - ", Container::Vertical({
		Checkbox("enable", &config.aimbot.b_aim_enable),
		Slider("smooth: ", &config.aimbot.f_aim_smooth, 1.f, 360.f, 1.f),
		Slider("   fov: ", &config.aimbot.f_aim_fov, 1.f, 180.f, 1.f),
	}));

	// Bhop
	const auto bhop_menu = wrap_menu(" - bhop - ", Container::Vertical({
		Checkbox("enable", &config.misc.b_enable_bhop),
	}));

	// Bhop
	const auto edgejump_menu = wrap_menu(" - edge jump - ", Container::Vertical({
		Checkbox("enable", &config.misc.b_enable_ej),
	}));

	// Glow
	const auto glow_menu = wrap_menu(" - glow - ", Container::Vertical({
		Checkbox("enable", &config.visuals.b_glow_enable),
		Checkbox("health based", &config.visuals.b_glow_health_based),
		Checkbox("visible only", &config.visuals.b_glow_visible_only),
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
	const auto skinchanger_menu = wrap_menu(" - skin changer - ", Container::Vertical({
		Checkbox("enable", &config.visuals.b_sc_enable),
		Checkbox("set paint kit", &config.visuals.b_sc_set_paint_kit),
		Input(&var::skins::str_paint_kit, "paint kit"),
		Container::Horizontal({
			Dropdown(&var::skins::models, &config.visuals.i_sc_selected_model_index),
		}),
	}));

	// Trigger bot
	const auto triggerbot_menu = wrap_menu(" - trigger - ", Container::Vertical({
		Checkbox("enable", &config.aimbot.b_trigger_enable),
	}));

	// Config
	const auto config_menu = wrap_menu(" - config - ", Container::Vertical({
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
		"Aimbot  ",
		"Visuals  ",
		"Misc  ",
		"Players  ",
		"Config  "
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
	auto tab_container = Container::Tab({
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
			render_menu()->Render(),
			separator() | dim,
			hbox({
				tab_menu->Render(),
				separator(),
				frame(tab_container->Render()),
			}) | flex | border,
		});
	});

	screen.Loop(component);
}

Component c_tui::render_menu() {
	return Renderer([&] {
		return hbox({
			text("external"),
			separator(),
			text("glow") | color(Color::RGB((uint8_t)config.visuals.f_glow_r, (uint8_t)config.visuals.f_glow_g, (uint8_t)config.visuals.f_glow_b)),
		}) | border;
	});
}

Component c_tui::wrap_menu(std::string name, Component component) {
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