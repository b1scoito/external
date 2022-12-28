#include "pch.hpp"
#include "sdk.hpp"

bool c_basesdk::run()
{
	// Wait for CS:GO to open
	std::cout << xorstr("Waiting for CS:GO to open...\n");
	do
	{
		proc = process::get_by_name(var::cs::str_process);
		timer::sleep(250);
	} while (!proc.is_running());

	// Attach memory to process
	std::cout << xorstr("Attaching to process\n");
	g_memory->attach();

	// Check for outdated offsets
	if (!sdk::base->check_for_version_mismatch())
	{
		std::cout << xorstr("Cheat is outdated! exiting.\n");
		timer::sleep(3000);

		return false;
	}

	// Close cheat when CS:GO closes thread
	std::thread([&]
				{
		while ( proc.is_running() )
			timer::sleep( 1000 );

		std::exit( EXIT_SUCCESS ); })
		.detach();

	// Wait for vstdlib.dll to load
	std::cout << xorstr("Waiting for vstdlib.dll to load...\n");
	do
	{
		g_memory->get_module(xorstr(L"vstdlib.dll"), vstdlib);
		timer::sleep(250);
	} while (get_vstdlib_image().base <= 0x0);

	std::cout << xorstr("vstdlib.dll -> ") << std::hex << get_vstdlib_image().base << std::endl;

	// Wait for engine.dll to load
	std::cout << xorstr("Waiting for engine.dll to load...\n");
	do
	{
		g_memory->get_module(xorstr(L"engine.dll"), engine);
		timer::sleep(250);
	} while (get_engine_image().base <= 0x0);

	std::cout << xorstr("engine.dll -> ") << std::hex << get_engine_image().base << std::endl;

	// Wait for client.dll to load
	std::cout << xorstr("Waiting for client.dll to load...\n");
	do
	{
		g_memory->get_module(xorstr(L"client.dll"), client);
		timer::sleep(250);
	} while (get_client_image().base <= 0x0);

	std::cout << xorstr("client.dll -> ") << std::hex << get_client_image().base << std::endl;

	// Get the window
	std::cout << xorstr("Waiting for window class handle...\n");
	do
	{
		var::cs::h_wnd = FindWindow(xorstr(L"Valve001"), nullptr);
		timer::sleep(100);
	} while (!var::cs::h_wnd);

	return true;
}

const bool c_basesdk::check_for_version_mismatch() const
{
	wchar_t filename[MAX_PATH] = {};
	if (!GetModuleFileNameEx(g_memory->get_handle(), NULL, filename, MAX_PATH))
		return false;

	const std::wstring name = filename;
	const auto path = name.substr(0, name.find_last_of(xorstr(L"/\\"))) + xorstr(L"\\csgo\\steam.inf");

	std::ifstream in(path);
	std::string line = {};
	if (in.good())
		std::getline(in, line);

	const auto csgo_version = string::split(line, "=")[1];

	if (sdk::current_game_version != csgo_version)
		return false;

	return true;
}

c_basesdk::~c_basesdk()
{
	g_memory->unload();
}