#include "pch.hpp"
#include "entity.hpp"

std::int32_t c_entity::get_health() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iHealth);
}

std::int32_t c_entity::get_team() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iTeamNum);
}

std::int32_t c_entity::get_flags() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_fFlags);
}

std::int32_t c_entity::glow_index() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iGlowIndex);
}

std::int32_t c_entity::crosshair_id() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_iCrosshairId);
}

bool c_entity::is_dormant() const
{
	return g_memory->read<bool>(base_address + sdk::offsets::m_bDormant);
}

bool c_entity::is_scoped() const
{
	return g_memory->read<bool>(base_address + sdk::netvars::m_bIsScoped);
}

bool c_entity::is_spotted() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_bSpottedByMask);
}

bool c_entity::is_visible_ray() const
{
	return var::bsp::parsed_map ? var::bsp::bp.is_visible(rn::vector3(g_local.eye_pos().x, 
		g_local.eye_pos().y, g_local.eye_pos().z), rn::vector3(this->eye_pos().x,
			this->eye_pos().y, this->eye_pos().z)) : false;
}

bool c_entity::has_immunity() const
{
	return g_memory->read<bool>(base_address + sdk::netvars::m_bGunGameImmunity);
}

std::int32_t c_entity::move_type() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_MoveType);
}

std::int32_t c_entity::life_state() const
{
	return g_memory->read<std::int32_t>(base_address + sdk::netvars::m_lifeState);
}

Vector c_entity::get_velocity() const
{
	return g_memory->read<Vector>(base_address + sdk::netvars::m_vecVelocity);
}

std::int32_t c_entity::get_class_id() const
{
	const auto IClientNetworkable = g_memory->read<std::uintptr_t>(base_address + 0x8);		  // IClientNetworkable vtable
	const auto GetClientClass = g_memory->read<std::uintptr_t>(IClientNetworkable + 2 * 0x4); // 3rd function in the vtable (GetClientClass)
	const auto GetClientClass_ptr = g_memory->read<std::uintptr_t>(GetClientClass + 0x1);	  // pointer to the ClientClass struct out of the mov eax

	return g_memory->read<std::int32_t>(GetClientClass_ptr + 0x14); // ClassID
}

Vector c_entity::bone_matrix(int bone) const
{
	const auto matrix = g_memory->read<std::uintptr_t>(base_address + sdk::netvars::m_dwBoneMatrix);

	Vector vec_matrix = {
		g_memory->read<float>(matrix + 0x30 * bone + 0xC),
		g_memory->read<float>(matrix + 0x30 * bone + 0x1C),
		g_memory->read<float>(matrix + 0x30 * bone + 0x2C)};

	return vec_matrix;
}

Vector c_entity::eye_pos() const
{
	return g_memory->read<Vector>(base_address + sdk::netvars::m_vecOrigin) + g_memory->read<Vector>(base_address + sdk::netvars::m_vecViewOffset);
}

Vector c_entity::view_offset() const {
	return g_memory->read<Vector>(base_address + sdk::netvars::m_vecViewOffset);
}

Vector c_entity::origin() const {
	return g_memory->read<Vector>(base_address + sdk::netvars::m_vecOrigin);
}

Vector c_entity::aim_punch() const
{
	return g_memory->read<Vector>(base_address + sdk::netvars::m_aimPunchAngle);
}

bool c_entity::is_alive() const
{
	return (this->life_state() == sdk::structs::e_life_state::LIFE_ALIVE);
}

std::uintptr_t c_entity::get_view_model() const 
{
	return g_memory->read<std::uintptr_t>(g_local.get_entity() + sdk::netvars::m_hViewModel);
}

bool c_entity::is_localplayer() const
{
	return (base_address == g_local.get_entity());
}

// From: https://github.com/rollraw/qo0-base/blob/f6ded6392dbb9e433c279fdb6fc3843398b9e1c7/base/sdk/entity.cpp#L212
bool c_entity::is_enemy() const
{
	auto mp_teammates_are_enemies = g_convar->find(xorstr("mp_teammates_are_enemies"));
	if (!mp_teammates_are_enemies.get_pointer())
		return false;

	auto teammates_are_enemies = mp_teammates_are_enemies.get_int();
	teammates_are_enemies ^= mp_teammates_are_enemies.get_pointer();

	return teammates_are_enemies ? true : this->get_team() != g_local.get_team();
}

c_weapon c_entity::get_weapon() const
{
	const auto current_weapon = g_memory->read<std::uintptr_t>(this->base_address + sdk::netvars::m_hActiveWeapon);
	if (!current_weapon)
		return c_weapon(NULL);

	const auto current_weapon_entity = g_memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwEntityList + ((current_weapon & 0xFFF) - 1) * 0x10);
	if (!current_weapon_entity)
		return c_weapon(NULL);

	return c_weapon(current_weapon_entity);
}

sdk::structs::playerinfo_t c_entity::get_player_info() const {
	const auto player_info_items = g_memory->read<std::uintptr_t>(g_memory->read<std::uintptr_t>(g_engine->get_user_info_table() + 0x40) + 0xC);
	return g_memory->read<sdk::structs::playerinfo_t>(g_memory->read<std::uintptr_t>(player_info_items + 0x28 + (this->index * 0x34)));
}