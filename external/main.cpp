#include "pch.hpp"

// features
#include "bhop.hpp"
#include "glow.hpp"
#include "triggerbot.hpp"
#include "skinchanger.hpp"
#include "aimbot.hpp"

// sdk
#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"
#include "convar.hpp"

// menu
#include "tui.hpp"

// cache
#include "on_update.hpp"
#include "on_entity.hpp"

int main(int argc, const char *argv[]) {
	std::atexit([]{ var::b_is_running = false; });

	// Run SDK
	if (!sdk::base->run())
		return EXIT_FAILURE;

	// Run config system
	config.run("external");

	// Run update threads
	std::thread(on_update_cache).detach();
	std::thread(on_entity_cache).detach();

	// Run cheat threads
	std::thread(&c_bhop::run, g_bhop.get()).detach();
	std::thread(&c_glow::run, g_glow.get()).detach();
	std::thread(&c_triggerbot::run, g_triggerbot.get()).detach();
	std::thread(&c_skinchanger::run, g_skinchanger.get()).detach();
	std::thread(&c_aimbot::run, g_aimbot.get()).detach();

	// Wait until stop signal
	g_tui->render();

	var::b_is_running = false;

	return EXIT_SUCCESS;
}