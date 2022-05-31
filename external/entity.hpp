#pragma once
#include "vector.hpp"
#include "convar.hpp"

class c_entity
{
private:
	std::uintptr_t base_address = {};

public:
	c_entity() = default;
	c_entity( const std::uintptr_t base_addr )
	{
		this->base_address = base_addr;
	}

public: // Read
	constexpr auto& get_entity() const
	{
		return base_address;
	}

	const auto get_health() const
	{
		return g_memory->read<std::int32_t>( base_address + sdk::netvars::m_iHealth );
	}

	const auto get_team() const
	{
		return g_memory->read<std::int32_t>( base_address + sdk::netvars::m_iTeamNum );
	}

	const auto get_flags() const
	{
		return g_memory->read<std::int32_t>( base_address + sdk::netvars::m_fFlags );
	}

	const auto glow_index() const
	{
		return g_memory->read<std::int32_t>( base_address + sdk::netvars::m_iGlowIndex );
	}

	const auto crosshair_id() const
	{
		return g_memory->read<std::int32_t>( base_address + sdk::netvars::m_iCrosshairId );
	}

	const auto is_dormant() const
	{
		return g_memory->read<bool>( base_address + sdk::offsets::m_bDormant );
	}

	const auto has_immunity() const
	{
		return g_memory->read<bool>( base_address + sdk::netvars::m_bGunGameImmunity );
	}

	const auto move_type() const
	{
		return g_memory->read<std::int32_t>( base_address + sdk::netvars::m_MoveType );
	}

	const auto life_state() const
	{
		return g_memory->read<std::int32_t>( base_address + sdk::netvars::m_lifeState );
	}

	const auto get_velocity() const
	{
		return g_memory->read<Vector>( base_address + sdk::netvars::m_vecVelocity );
	}

	const auto bone_matrix( const int& bone ) const
	{
		const auto matrix = g_memory->read<std::ptrdiff_t>( base_address + sdk::netvars::m_dwBoneMatrix );

		Vector vec_matrix = {};
		vec_matrix.x = g_memory->read<float>( matrix + 0x30 * bone + 0xC );
		vec_matrix.y = g_memory->read<float>( matrix + 0x30 * bone + 0x1C );
		vec_matrix.z = g_memory->read<float>( matrix + 0x30 * bone + 0x2C );

		return vec_matrix;
	}

	const auto is_alive() const
	{
		return this->life_state() == sdk::structs::life_state::LIFE_ALIVE;
	}

	const auto is_localplayer() const
	{
		return base_address == g_client->get_local_player_address();
	}

	// From: https://github.com/rollraw/qo0-base/blob/f6ded6392dbb9e433c279fdb6fc3843398b9e1c7/base/sdk/entity.cpp#L212
	const auto is_enemy() const
	{
		const auto local = c_entity( g_client->get_local_player_address() );

		auto mp_teammates_are_enemies = g_convar->find( "mp_teammates_are_enemies" );
		if ( !mp_teammates_are_enemies.get_pointer() )
			return false;
			
		auto value = mp_teammates_are_enemies.get_int();
		value ^= mp_teammates_are_enemies.get_pointer();

		return value ? true : this->get_team() != local.get_team();
	}
};

inline auto g_local = c_entity();