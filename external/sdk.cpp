#include "pch.hpp"
#include "sdk.hpp"

bool c_basesdk::run()
{
	// Wait for CS:GO to open
	log_debug( xorstr( "Waiting for CS:GO to open..." ) );
	do
	{
		proc = process::get_by_name( var::game::str_process );
		timer::sleep( 250 );
	}
	while ( !proc.is_running() );

	// Attach memory to process
	log_debug( xorstr( "Attaching to process" ) );
	g_memory->attach();

	// Check for outdated offsets
	if ( !sdk::base->check_for_outdated_offsets() )
	{
		log_debug( xorstr( "Cheat is outdated! exiting." ) );
		timer::sleep( 3000 );

		return false;
	}

	// Close cheat when CS:GO closes thread
	std::thread( [&]
	{
		while ( proc.is_running() )
			timer::sleep( 100 );

		std::exit( EXIT_SUCCESS );
	} ).detach();

	// Wait for engine.dll to load
	log_debug( xorstr( "Waiting for engine.dll to load..." ) );
	do
	{
		g_memory->get_module( xorstr( L"engine.dll" ), engine );
		timer::sleep( 250 );
	}
	while ( get_engine_image().base <= 0x0 );

	log_debug( xorstr( "engine.dll -> 0x%x" ), get_engine_image().base );

	// Wait for client.dll to load
	log_debug( xorstr( "Waiting for client.dll to load..." ) );
	do
	{
		g_memory->get_module( xorstr( L"client.dll" ), client );
		timer::sleep( 250 );
	}
	while ( get_client_image().base <= 0x0 );

	log_debug( xorstr( "client.dll -> 0x%x" ), get_client_image().base );

	// Get the window
	log_debug( xorstr( "Waiting for window class handle..." ) );
	do
	{
		var::game::wnd = FindWindow( xorstr( L"Valve001" ), nullptr );
		timer::sleep( 100 );
	}
	while ( !var::game::wnd );

	return true;
}

const bool c_basesdk::check_for_outdated_offsets() const
{
	wchar_t filename[MAX_PATH] = {};
	if ( !GetModuleFileNameEx( g_memory->get_handle(), NULL, filename, MAX_PATH ) )
		return false;

	const std::wstring name = filename;
	const auto path = name.substr( 0, name.find_last_of( xorstr( L"/\\" ) ) ) + xorstr( L"\\csgo\\steam.inf" );

	std::ifstream in( path );
	std::string line = {};
	if ( in.good() )
		std::getline( in, line );

	const auto csgo_version = string::split( line, "=" )[1];

	if ( var::game::current_game_version != csgo_version )
		return false;

	return true;
}

c_basesdk::~c_basesdk()
{
	g_memory->unload();
}