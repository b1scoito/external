#include "pch.hpp"

// menu
#include "menu.hpp"

// features
#include "aimbot.hpp"
#include "bhop.hpp"
#include "glow.hpp"
#include "edgejump.hpp"
#include "skinchanger.hpp"
#include "triggerbot.hpp"

// cache
#include "on_entity.hpp"
#include "on_world.hpp"

int main(int argc, const char *argv[]) {
	std::atexit([]{ var::b_is_running = false; });

	// Run SDK
	if (!sdk::base->run())
		return EXIT_FAILURE;

	// Run config system
	config.run("external");

	// Run update threads
	// TODO: Finish proper caching
	std::thread(on_world_cache).detach();
	std::thread(on_entity_cache).detach();

	// Run cheat threads
	// Fix: aimbot, edgejump
	// Add: more features to: glow, skin changer
	// Change: triggerbot logic
	std::thread(&c_aimbot::run, g_aimbot.get()).detach();
	std::thread(&c_bhop::run, g_bhop.get()).detach();
	std::thread(&c_glow::run, g_glow.get()).detach();
	std::thread(&c_edgejump::run, g_edgejump.get()).detach();
	std::thread(&c_skinchanger::run, g_skinchanger.get()).detach();
	std::thread(&c_triggerbot::run, g_triggerbot.get()).detach();

	// TODO: See what's causing all loops to lag after implementing ImGui
	// Wait until stop signal
	if (!g_menu->setup())
	{
		g_menu->destroy();
		return EXIT_FAILURE;
	}

	// Render loop
	g_menu->render();

	var::b_is_running = false;

	return EXIT_SUCCESS;
}