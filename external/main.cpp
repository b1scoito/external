#include "pch.hpp"

#include "bhop.hpp"
#include "glow.hpp"

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	std::atexit([] { var::b_is_running = false; });

	// Run SDK
	sdk::base->run();

	// Run bhop
	bhop->run();

	// Run glow
	glow->run(var::keybinds::toggle_glow_keybind);

	while (!(GetAsyncKeyState(VK_DELETE)))
		std::this_thread::sleep_for(50ms);

	var::b_is_running = false;
	
	return EXIT_SUCCESS;
}