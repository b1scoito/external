#include "pch.hpp"

#include "client.hpp"
#include "engine.hpp"
#include "sdk.hpp"

const std::uintptr_t c_client::get_local_player_address() const
{
	const auto local_player_index = g_memory->read<std::int32_t>( g_engine->get_client_state() + sdk::offsets::dwClientState_GetLocalPlayer );
	const auto local_player = g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwEntityList + 0x10 * local_player_index );

	return local_player;
}

const bool c_client::in_menu() const
{
	CURSORINFO ci{ sizeof( CURSORINFO ) };
	if ( !GetCursorInfo( &ci ) )
		return false;

	const auto handle = ci.hCursor;
	if ( (handle > (HCURSOR)50000) && (handle < (HCURSOR)100000) )
		return true;

	return false;
}

const std::int32_t c_client::get_game_type() const
{
	const auto game_rules_proxy = g_memory->read<std::uintptr_t>( sdk::offsets::dwGameRulesProxy );
	const auto game_type = g_memory->read<std::int32_t>( game_rules_proxy + sdk::netvars::m_SurvivalGameRuleDecisionTypes );

	return game_type;
}

const std::uintptr_t c_client::get_glow_object_manager() const
{
	return g_memory->read<std::uintptr_t>( sdk::base->get_client_image().base + sdk::offsets::dwGlowObjectManager );
}

const std::int32_t c_client::get_force_jump() const
{
	return g_memory->read<std::int32_t>( sdk::base->get_client_image().base + sdk::offsets::dwForceJump );
}

const std::int32_t c_client::get_force_attack() const
{
	return g_memory->read<std::int32_t>( sdk::base->get_client_image().base + sdk::offsets::dwForceAttack );
}

const std::int32_t c_client::force_jump( const std::int32_t state ) const
{
	return g_memory->write<std::int32_t>( sdk::base->get_client_image().base + sdk::offsets::dwForceJump, state );
}

const std::int32_t c_client::force_attack( const std::int32_t state ) const
{
	return g_memory->write<std::int32_t>( sdk::base->get_client_image().base + sdk::offsets::dwForceAttack, state );
}