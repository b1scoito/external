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
	const auto kb = keybind(true, keybind_state_t::toggle, VK_HOME);
	glow->run(kb);

	while (!(GetAsyncKeyState(VK_DELETE)))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

	var::b_is_running = false;
	
	return EXIT_SUCCESS;
}