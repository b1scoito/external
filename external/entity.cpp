#include "pch.hpp"

#include "entity.hpp"
#include "vector.hpp"
#include "convar.hpp"
#include "sdk.hpp"

const std::int32_t c_entity::get_health() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iHealth);
}

const std::int32_t c_entity::get_team() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iTeamNum);
}

const std::int32_t c_entity::get_flags() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_fFlags);
}

const std::int32_t c_entity::glow_index() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iGlowIndex);
}

const std::int32_t c_entity::crosshair_id() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iCrosshairId);
}

const bool c_entity::is_dormant() const
{
	return g_memory->read<bool>(base_address + sdk::offsets::m_bDormant);
}

const bool c_entity::is_scoped() const
{
	return g_memory->read<bool>(base_address + sdk::netvars::m_bIsScoped);
}

const std::int32_t c_entity::is_spotted() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_bSpottedByMask);
}

const bool c_entity::has_immunity() const
{
	return g_memory->read<bool>(base_address + sdk::netvars::m_bGunGameImmunity);
}

const std::int32_t c_entity::move_type() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_MoveType);
}

const std::int32_t c_entity::life_state() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_lifeState);
}

const Vector c_entity::get_velocity() const
{
	return g_memory->read<Vector>(base_address + sdk::netvars::m_vecVelocity);
}

const std::int32_t c_entity::get_class_id() const
{
	const auto IClientNetworkable = g_memory->read<std::uintptr_t>(base_address + 0x8);		  // IClientNetworkable vtable
	const auto GetClientClass = g_memory->read<std::uintptr_t>(IClientNetworkable + 2 * 0x4); // 3rd function in the vtable (GetClientClass)
	const auto GetClientClass_ptr = g_memory->read<std::uintptr_t>(GetClientClass + 0x1);	  // pointer to the ClientClass struct out of the mov eax

	return g_memory->read<std::int32_t>(GetClientClass_ptr + 0x14); // ClassID
}

const Vector c_entity::bone_matrix(const int &bone) const
{
	const auto matrix = g_memory->read<std::uintptr_t>(base_address + sdk::netvars::m_dwBoneMatrix);

	Vector vec_matrix = {
		g_memory->read<float>(matrix + 0x30 * bone + 0xC),
		g_memory->read<float>(matrix + 0x30 * bone + 0x1C),
		g_memory->read<float>(matrix + 0x30 * bone + 0x2C)};

	return vec_matrix;
}

const Vector c_entity::eye_position() const
{
	const auto vec_eye_pos = g_memory->read<Vector>(base_address + sdk::netvars::m_vecOrigin) + g_memory->read<Vector>(base_address + sdk::netvars::m_vecViewOffset);
	return vec_eye_pos;
}

const Vector c_entity::aim_punch() const
{
	return g_memory->read<Vector>(base_address + sdk::netvars::m_aimPunchAngle);
}

const bool c_entity::is_alive() const
{
	return (this->life_state() == sdk::structs::life_state::LIFE_ALIVE);
}

const bool c_entity::is_localplayer() const
{
	return (base_address == g_local.get_entity());
}

// From: https://github.com/rollraw/qo0-base/blob/f6ded6392dbb9e433c279fdb6fc3843398b9e1c7/base/sdk/entity.cpp#L212
const bool c_entity::is_enemy() const
{
	auto mp_teammates_are_enemies = g_convar->find(xorstr("mp_teammates_are_enemies"));
	if (!mp_teammates_are_enemies.get_pointer())
		return false;

	auto teammates_are_enemies = mp_teammates_are_enemies.get_int();
	teammates_are_enemies ^= mp_teammates_are_enemies.get_pointer();

	return teammates_are_enemies ? true : this->get_team() != g_local.get_team();
}