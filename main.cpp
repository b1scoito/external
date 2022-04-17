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
	// glow->run();

	return EXIT_SUCCESS;
}