#include "pch.hpp"

#include "bhop.hpp"
#include "glow.hpp"
#include "triggerbot.hpp"

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	std::atexit([] { var::b_is_running = false; });

	// Run SDK
	sdk::base->run();

	// Run bhop
	bhop->run();

	// Run glow
	glow->run(var::keybinds::toggle_glow_key);

	// Run triggerbot
	triggerbot->run(var::keybinds::hold_triggerbot_key);

	while (!GetAsyncKeyState(VK_DELETE))
		timer::sleep(50);

	var::b_is_running = false;
	
	return EXIT_SUCCESS;
}