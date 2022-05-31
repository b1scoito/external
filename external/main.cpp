#include "pch.hpp"

#include "bhop.hpp"
#include "glow.hpp"
#include "triggerbot.hpp"

#include "engine.hpp"
#include "client.hpp"
#include "entity.hpp"
#include "convar.hpp"

INT WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	std::atexit( []
	{
		var::b_is_running = false;
	} );

	// Run SDK
	if ( !sdk::base->run() )
		return EXIT_FAILURE;

	// Run bhop
	bhop->run();

	// Run glow
	glow->run( var::keybinds::toggle_glow_key );

	// Run triggerbot
	triggerbot->run( var::keybinds::hold_triggerbot_key );

	while ( !GetAsyncKeyState( VK_DELETE ) )
	{
		timer::sleep( 100 );

		// Cache
		if ( !g_engine->in_game() )
		{
			g_local = c_entity();
			g_convar_list.clear();

			continue;
		}

		if ( !g_local.get_entity() )
			g_local = c_entity( g_client->get_local_player_address() );

		if ( g_convar_list.empty() )
			g_convar->populate_list();
	}

	var::b_is_running = false;

	return EXIT_SUCCESS;
}