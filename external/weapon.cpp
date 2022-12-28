#include "pch.hpp"
#include "weapon.hpp"

const bool c_weapon::is_sniper() const {
	return false;
}
const bool c_weapon::is_pistol() const {
	return false;
}
const bool c_weapon::is_knife() const {
	static const std::vector<sdk::structs::item_definitions> knives = {
		sdk::structs::WEAPON_KNIFE_GG,
		sdk::structs::WEAPON_KNIFE,
		sdk::structs::WEAPON_KNIFE_T,
		sdk::structs::WEAPON_KNIFE_GHOST,
		sdk::structs::WEAPON_KNIFE_BAYONET,
		sdk::structs::WEAPON_KNIFE_CSS,
		sdk::structs::WEAPON_KNIFE_FLIP,
		sdk::structs::WEAPON_KNIFE_GUT,
		sdk::structs::WEAPON_KNIFE_KARAMBIT,
		sdk::structs::WEAPON_KNIFE_M9_BAYONET,
		sdk::structs::WEAPON_KNIFE_TACTICAL,
		sdk::structs::WEAPON_KNIFE_FALCHION,
		sdk::structs::WEAPON_KNIFE_SURVIVAL_BOWIE,
		sdk::structs::WEAPON_KNIFE_BUTTERFLY,
		sdk::structs::WEAPON_KNIFE_PUSH,
		sdk::structs::WEAPON_KNIFE_CORD,
		sdk::structs::WEAPON_KNIFE_CANIS,
		sdk::structs::WEAPON_KNIFE_URSUS,
		sdk::structs::WEAPON_KNIFE_GYPSY_JACKKNIFE,
		sdk::structs::WEAPON_KNIFE_OUTDOOR,
		sdk::structs::WEAPON_KNIFE_STILETTO,
		sdk::structs::WEAPON_KNIFE_WIDOWMAKER,
		sdk::structs::WEAPON_KNIFE_SKELETON,
	};
	return std::find(knives.begin(), knives.end(), this->index) != knives.end();
}

const bool c_weapon::is_grenade() const {
	return false;
}