#pragma once

#include <cstdint>

// 2022-12-17 02:01:15.156766200 UTC

namespace sdk
{
	constexpr ::std::int64_t timestamp = 1671242475;
	inline std::string current_game_version = xorstr("1539");

	namespace netvars
	{
		static constexpr std::uintptr_t cs_gamerules_data = 0x0;
		static constexpr std::uintptr_t m_ArmorValue = 0x117CC;
		static constexpr std::uintptr_t m_Collision = 0x320;
		static constexpr std::uintptr_t m_CollisionGroup = 0x474;
		static constexpr std::uintptr_t m_Local = 0x2FCC;
		static constexpr std::uintptr_t m_MoveType = 0x25C;
		static constexpr std::uintptr_t m_OriginalOwnerXuidHigh = 0x31D4;
		static constexpr std::uintptr_t m_OriginalOwnerXuidLow = 0x31D0;
		static constexpr std::uintptr_t m_SurvivalGameRuleDecisionTypes = 0x1328;
		static constexpr std::uintptr_t m_SurvivalRules = 0xD00;
		static constexpr std::uintptr_t m_aimPunchAngle = 0x303C;
		static constexpr std::uintptr_t m_aimPunchAngleVel = 0x3048;
		static constexpr std::uintptr_t m_angEyeAnglesX = 0x117D0;
		static constexpr std::uintptr_t m_angEyeAnglesY = 0x117D4;
		static constexpr std::uintptr_t m_bBombDefused = 0x29C0;
		static constexpr std::uintptr_t m_bBombPlanted = 0x9A5;
		static constexpr std::uintptr_t m_bBombTicking = 0x2990;
		static constexpr std::uintptr_t m_bFreezePeriod = 0x20;
		static constexpr std::uintptr_t m_bGunGameImmunity = 0x9990;
		static constexpr std::uintptr_t m_bHasDefuser = 0x117DC;
		static constexpr std::uintptr_t m_bHasHelmet = 0x117C0;
		static constexpr std::uintptr_t m_bInReload = 0x32B5;
		static constexpr std::uintptr_t m_bIsDefusing = 0x997C;
		static constexpr std::uintptr_t m_bIsQueuedMatchmaking = 0x74;
		static constexpr std::uintptr_t m_bIsScoped = 0x9974;
		static constexpr std::uintptr_t m_bIsValveDS = 0x7C;
		static constexpr std::uintptr_t m_bSpotted = 0x93D;
		static constexpr std::uintptr_t m_bSpottedByMask = 0x980;
		static constexpr std::uintptr_t m_bStartedArming = 0x3400;
		static constexpr std::uintptr_t m_bUseCustomAutoExposureMax = 0x9D9;
		static constexpr std::uintptr_t m_bUseCustomAutoExposureMin = 0x9D8;
		static constexpr std::uintptr_t m_bUseCustomBloomScale = 0x9DA;
		static constexpr std::uintptr_t m_clrRender = 0x70;
		static constexpr std::uintptr_t m_dwBoneMatrix = 0x26A8;
		static constexpr std::uintptr_t m_fAccuracyPenalty = 0x3340;
		static constexpr std::uintptr_t m_fFlags = 0x104;
		static constexpr std::uintptr_t m_flC4Blow = 0x29A0;
		static constexpr std::uintptr_t m_flCustomAutoExposureMax = 0x9E0;
		static constexpr std::uintptr_t m_flCustomAutoExposureMin = 0x9DC;
		static constexpr std::uintptr_t m_flCustomBloomScale = 0x9E4;
		static constexpr std::uintptr_t m_flDefuseCountDown = 0x29BC;
		static constexpr std::uintptr_t m_flDefuseLength = 0x29B8;
		static constexpr std::uintptr_t m_flFallbackWear = 0x31E0;
		static constexpr std::uintptr_t m_flFlashDuration = 0x10470;
		static constexpr std::uintptr_t m_flFlashMaxAlpha = 0x1046C;
		static constexpr std::uintptr_t m_flLastBoneSetupTime = 0x2928;
		static constexpr std::uintptr_t m_flLowerBodyYawTarget = 0x9ADC;
		static constexpr std::uintptr_t m_flNextAttack = 0x2D80;
		static constexpr std::uintptr_t m_flNextPrimaryAttack = 0x3248;
		static constexpr std::uintptr_t m_flSimulationTime = 0x268;
		static constexpr std::uintptr_t m_flTimerLength = 0x29A4;
		static constexpr std::uintptr_t m_hActiveWeapon = 0x2F08;
		static constexpr std::uintptr_t m_hBombDefuser = 0x29C4;
		static constexpr std::uintptr_t m_hMyWeapons = 0x2E08;
		static constexpr std::uintptr_t m_hObserverTarget = 0x339C;
		static constexpr std::uintptr_t m_hOwner = 0x29DC;
		static constexpr std::uintptr_t m_hOwnerEntity = 0x14C;
		static constexpr std::uintptr_t m_hViewModel = 0x3308;
		static constexpr std::uintptr_t m_iAccountID = 0x2FD8;
		static constexpr std::uintptr_t m_iClip1 = 0x3274;
		static constexpr std::uintptr_t m_iCompetitiveRanking = 0x1A84;
		static constexpr std::uintptr_t m_iCompetitiveWins = 0x1B88;
		static constexpr std::uintptr_t m_iCrosshairId = 0x11838;
		static constexpr std::uintptr_t m_iDefaultFOV = 0x333C;
		static constexpr std::uintptr_t m_iEntityQuality = 0x2FBC;
		static constexpr std::uintptr_t m_iFOV = 0x31F4;
		static constexpr std::uintptr_t m_iFOVStart = 0x31F8;
		static constexpr std::uintptr_t m_iGlowIndex = 0x10488;
		static constexpr std::uintptr_t m_iHealth = 0x100;
		static constexpr std::uintptr_t m_iItemDefinitionIndex = 0x2FBA;
		static constexpr std::uintptr_t m_iItemIDHigh = 0x2FD0;
		static constexpr std::uintptr_t m_iMostRecentModelBoneCounter = 0x2690;
		static constexpr std::uintptr_t m_iObserverMode = 0x3388;
		static constexpr std::uintptr_t m_iShotsFired = 0x103E0;
		static constexpr std::uintptr_t m_iState = 0x3268;
		static constexpr std::uintptr_t m_iTeamNum = 0xF4;
		static constexpr std::uintptr_t m_iViewModelIndex = 0x3250;
		static constexpr std::uintptr_t m_lifeState = 0x25F;
		static constexpr std::uintptr_t m_nBombSite = 0x2994;
		static constexpr std::uintptr_t m_nFallbackPaintKit = 0x31D8;
		static constexpr std::uintptr_t m_nFallbackSeed = 0x31DC;
		static constexpr std::uintptr_t m_nFallbackStatTrak = 0x31E4;
		static constexpr std::uintptr_t m_nForceBone = 0x268C;
		static constexpr std::uintptr_t m_nModelIndex = 0x258;
		static constexpr std::uintptr_t m_nTickBase = 0x3440;
		static constexpr std::uintptr_t m_nViewModelIndex = 0x29D0;
		static constexpr std::uintptr_t m_rgflCoordinateFrame = 0x444;
		static constexpr std::uintptr_t m_szCustomName = 0x304C;
		static constexpr std::uintptr_t m_szLastPlaceName = 0x35C4;
		static constexpr std::uintptr_t m_thirdPersonViewAngles = 0x31E8;
		static constexpr std::uintptr_t m_vecOrigin = 0x138;
		static constexpr std::uintptr_t m_vecVelocity = 0x114;
		static constexpr std::uintptr_t m_vecViewOffset = 0x108;
		static constexpr std::uintptr_t m_viewPunchAngle = 0x3030;
		static constexpr std::uintptr_t m_zoomLevel = 0x33E0;
	} // namespace netvars

	namespace offsets
	{
		static constexpr std::uintptr_t anim_overlays = 0x2990;
		static constexpr std::uintptr_t clientstate_choked_commands = 0x4D30;
		static constexpr std::uintptr_t clientstate_delta_ticks = 0x174;
		static constexpr std::uintptr_t clientstate_last_outgoing_command = 0x4D2C;
		static constexpr std::uintptr_t clientstate_net_channel = 0x9C;
		static constexpr std::uintptr_t convar_name_hash_table = 0x301A0;
		static constexpr std::uintptr_t dwClientState = 0x59F194;
		static constexpr std::uintptr_t dwClientState_GetLocalPlayer = 0x180;
		static constexpr std::uintptr_t dwClientState_IsHLTV = 0x4D48;
		static constexpr std::uintptr_t dwClientState_Map = 0x28C;
		static constexpr std::uintptr_t dwClientState_MapDirectory = 0x188;
		static constexpr std::uintptr_t dwClientState_MaxPlayer = 0x388;
		static constexpr std::uintptr_t dwClientState_PlayerInfo = 0x52C0;
		static constexpr std::uintptr_t dwClientState_State = 0x108;
		static constexpr std::uintptr_t dwClientState_ViewAngles = 0x4D90;
		static constexpr std::uintptr_t dwEntityList = 0x4DFFF14;
		static constexpr std::uintptr_t dwForceAttack = 0x322DD10;
		static constexpr std::uintptr_t dwForceAttack2 = 0x322DD1C;
		static constexpr std::uintptr_t dwForceBackward = 0x322DD40;
		static constexpr std::uintptr_t dwForceForward = 0x322DD34;
		static constexpr std::uintptr_t dwForceJump = 0x52BBC9C;
		static constexpr std::uintptr_t dwForceLeft = 0x322DD4C;
		static constexpr std::uintptr_t dwForceRight = 0x322DD58;
		static constexpr std::uintptr_t dwGameDir = 0x63AD80;
		static constexpr std::uintptr_t dwGameRulesProxy = 0x532F4CC;
		static constexpr std::uintptr_t dwGetAllClasses = 0xE0BFDC;
		static constexpr std::uintptr_t dwGlobalVars = 0x59EE58;
		static constexpr std::uintptr_t dwGlowObjectManager = 0x535A9D8;
		static constexpr std::uintptr_t dwInput = 0x525D4E8;
		static constexpr std::uintptr_t dwInterfaceLinkList = 0x99BC84;
		static constexpr std::uintptr_t dwLocalPlayer = 0xDEA964;
		static constexpr std::uintptr_t dwMouseEnable = 0x5239148;
		static constexpr std::uintptr_t dwMouseEnablePtr = 0x5239118;
		static constexpr std::uintptr_t dwPlayerResource = 0x322C0C0;
		static constexpr std::uintptr_t dwRadarBase = 0x52369EC;
		static constexpr std::uintptr_t dwSetClanTag = 0x8DA80;
		static constexpr std::uintptr_t dwViewMatrix = 0x4DF0D44;
		static constexpr std::uintptr_t dwWeaponTable = 0x525E5C4;
		static constexpr std::uintptr_t dwWeaponTableIndex = 0x326C;
		static constexpr std::uintptr_t dwbSendPackets = 0xDD072;
		static constexpr std::uintptr_t dwppDirect3DDevice9 = 0xA62C0;
		static constexpr std::uintptr_t find_hud_element = 0x3120FBD0;
		static constexpr std::uintptr_t force_update_spectator_glow = 0x3D91CA;
		static constexpr std::uintptr_t interface_engine_cvar = 0x3FA9C;
		static constexpr std::uintptr_t is_c4_owner = 0x3E69E0;
		static constexpr std::uintptr_t m_bDormant = 0xED;
		static constexpr std::uintptr_t m_bIsLocalPlayer = 0x3628;
		static constexpr std::uintptr_t m_flSpawnTime = 0x103C0;
		static constexpr std::uintptr_t m_pStudioHdr = 0x2950;
		static constexpr std::uintptr_t m_pitchClassPtr = 0x5239040;
		static constexpr std::uintptr_t model_ambient_min = 0x5A118C;
		static constexpr std::uintptr_t set_abs_angles = 0x1E72D0;
		static constexpr std::uintptr_t set_abs_origin = 0x1E7110;
	} // namespace offsets
} // namespace sdk
