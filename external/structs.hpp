#pragma once

namespace sdk
{
	namespace structs
	{
		struct globalvars_t
		{
			float	flRealTime;					// 0x00
			int		iFrameCount;				// 0x04
			float	flAbsFrameTime;				// 0x08
			float	flAbsFrameStartTime;		// 0x0C
			float	flCurrentTime;				// 0x10
			float	flFrameTime;				// 0x14
			int		nMaxClients;				// 0x18
			int		iTickCount;					// 0x1C
			float	flIntervalPerTick;			// 0x20
			float	flInterpolationAmount;		// 0x24
			int		nFrameSimulationTicks;		// 0x28
			int		iNetworkProtocol;			// 0x2C
			void* pSaveData;					// 0x30
			bool	bClient;					// 0x34
			bool	bRemoteClient;				// 0x35
			int		iTimestampNetworkingBase;	// 0x36
			int		iTimestampRandomizeWindow;	// 0x3A
		}; // Size: 0x3E

		class convar_t
		{
		public:
			char pad_0x0000[0x4];				// 0x00
			std::uintptr_t m_pNext;				// 0x04
			int m_bRegistered;					// 0x08 change to bool
			std::uintptr_t m_pszName;			// 0x0C
			std::uintptr_t m_pszDescription;	// 0x10
			int m_nFlags;						// 0x14
			char pad_0x0018[0x4];				// 0x18
			std::uintptr_t m_pParent;			// 0x1C
			std::uintptr_t m_pszDefaultValue;	// 0x20
			std::uintptr_t m_pszValue;			// 0x24
			int m_nSize;						// 0x28
			float m_flValue;					// 0x2C
			int m_nValue;						// 0x30
			int m_bHasMin;						// 0x34 change to bool
			float m_fMinVal;					// 0x38
			int m_bHasMax;						// 0x3C change to bool
			float m_fMaxVal;					// 0x40
		}; // Size: 0x44

		enum entity_glow_render_style : int
		{
			GLOWRENDERSTYLE_DEFAULT = 0,
			GLOWRENDERSTYLE_RIMGLOW3D,
			GLOWRENDERSTYLE_EDGE_HIGHLIGHT,
			GLOWRENDERSTYLE_EDGE_HIGHLIGHT_PULSE,
			GLOWRENDERSTYLE_COUNT
		};

		struct glow_object_t
		{
			void set( const float red, const float green, const float blue, const float alpha, const int nRenderStyle = GLOWRENDERSTYLE_DEFAULT ) // @note: styles not used cuz other styles doesnt have ignorez flag and needed to rebuild glow
			{
				this->R = red;
				this->G = green;
				this->B = blue;
				this->A = alpha;

				this->flBloomAmount = 1.0f;
				this->bRenderWhenOccluded = true;
				this->bRenderWhenUnoccluded = false;
				this->nRenderStyle = nRenderStyle;
			}

			std::int32_t			m_nNextFreeSlot;				// 0x00
			std::uint32_t			pEntity;						// 0x04
			float					R;								// 0x08
			float					G;								// 0x0C
			float					B;								// 0x10
			float					A;								// 0x14
			bool					bAlphaCappedByRenderAlpha;		// 0x18
			std::byte				pad0[0x3];						// 0x19 - pack 1 bool as 4 bytes
			float					flAlphaFunctionOfMaxVelocity;	// 0x1C
			float					flBloomAmount;					// 0x20
			float					flPulseOverdrive;				// 0x24
			bool					bRenderWhenOccluded;			// 0x28
			bool					bRenderWhenUnoccluded;			// 0x29
			bool					bFullBloomRender;				// 0x2A
			std::byte				pad1[0x1];						// 0x2B  - pack 3 bool as 4 bytes
			int						iFullBloomStencilTestValue;		// 0x2C
			int						nRenderStyle;					// 0x30
			int						nSplitScreenSlot;				// 0x34
		}; // Size: 0x38

		/* baseentity flags */
		enum flags : int
		{
			FL_ONGROUND = (1 << 0),
			FL_DUCKING = (1 << 1),
			FL_ANIMDUCKING = (1 << 2),
			FL_WATERJUMP = (1 << 3),
			FL_ONTRAIN = (1 << 4),
			FL_INRAIN = (1 << 5),
			FL_FROZEN = (1 << 6),
			FL_ATCONTROLS = (1 << 7),
			FL_CLIENT = (1 << 8),
			FL_FAKECLIENT = (1 << 9),
			FL_INWATER = (1 << 10),
			FL_FLY = (1 << 11),
			FL_SWIM = (1 << 12),
			FL_CONVEYOR = (1 << 13),
			FL_NPC = (1 << 14),
			FL_GODMODE = (1 << 15),
			FL_NOTARGET = (1 << 16),
			FL_AIMTARGET = (1 << 17),
			FL_PARTIALGROUND = (1 << 18),
			FL_STATICPROP = (1 << 19),
			FL_GRAPHED = (1 << 20),
			FL_GRENADE = (1 << 21),
			FL_STEPMOVEMENT = (1 << 22),
			FL_DONTTOUCH = (1 << 23),
			FL_BASEVELOCITY = (1 << 24),
			FL_WORLDBRUSH = (1 << 25),
			FL_OBJECT = (1 << 26),
			FL_KILLME = (1 << 27),
			FL_ONFIRE = (1 << 28),
			FL_DISSOLVING = (1 << 29),
			FL_TRANSRAGDOLL = (1 << 30),
			FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
		};

		enum move_type : int
		{
			MOVETYPE_NONE = 0,
			MOVETYPE_ISOMETRIC,
			MOVETYPE_WALK,
			MOVETYPE_STEP,
			MOVETYPE_FLY,
			MOVETYPE_FLYGRAVITY,
			MOVETYPE_VPHYSICS,
			MOVETYPE_PUSH,
			MOVETYPE_NOCLIP,
			MOVETYPE_LADDER,
			MOVETYPE_OBSERVER,
			MOVETYPE_CUSTOM,
			MOVETYPE_LAST = MOVETYPE_CUSTOM,
			MOVETYPE_MAX_BITS = 4
		};

		enum team_id : int
		{
			TEAM_UNASSIGNED = 0,
			TEAM_SPECTATOR,
			TEAM_TT,
			TEAM_CT
		};

		/* baseentity lifestate */
		enum life_state : int
		{
			LIFE_ALIVE = 0,
			LIFE_DYING,
			LIFE_DEAD,
			LIFE_RESPAWNABLE,
			LIFE_DISCARDBODY
		};

		enum bone_index : int
		{
			BONE_INVALID = -1,
			BONE_PELVIS,
			BONE_LEAN_ROOT,
			BONE_CAM_DRIVER,
			BONE_SPINE_0,
			BONE_SPINE_1,
			BONE_SPINE_2,
			BONE_SPINE_3,
			BONE_NECK,
			BONE_HEAD,
			BONE_CLAVICLE_L,
			BONE_ARM_UPPER_L,
			BONE_ARM_LOWER_L,
			BONE_HAND_L,
			BONE_FINGER_MIDDLE_META_L,
			BONE_FINGER_MIDDLE_0_L,
			BONE_FINGER_MIDDLE_1_L,
			BONE_FINGER_MIDDLE_2_L,
			BONE_FINGER_PINKY_META_L,
			BONE_FINGER_PINKY_0_L,
			BONE_FINGER_PINKY_1_L,
			BONE_FINGER_PINKY_2_L,
			BONE_FINGER_INDEX_META_L,
			BONE_FINGER_INDEX_0_L,
			BONE_FINGER_INDEX_1_L,
			BONE_FINGER_INDEX_2_L,
			BONE_FINGER_THUMB_0_L,
			BONE_FINGER_THUMB_1_L,
			BONE_FINGER_THUMB_2_L,
			BONE_FINGER_RING_META_L,
			BONE_FINGER_RING_0_L,
			BONE_FINGER_RING_1_L,
			BONE_FINGER_RING_2_L,
			BONE_WEAPON_HAND_L,
			BONE_ARM_LOWER_L_TWIST,
			BONE_ARM_LOWER_L_TWIST1,
			BONE_ARM_UPPER_L_TWIST,
			BONE_ARM_UPPER_L_TWIST1,
			BONE_CLAVICLE_R,
			BONE_ARM_UPPER_R,
			BONE_ARM_LOWER_R,
			BONE_HAND_R,
			BONE_FINGER_MIDDLE_META_R,
			BONE_FINGER_MIDDLE_0_R,
			BONE_FINGER_MIDDLE_1_R,
			BONE_FINGER_MIDDLE_2_R,
			BONE_FINGER_PINKY_META_R,
			BONE_FINGER_PINKY_0_R,
			BONE_FINGER_PINKY_1_R,
			BONE_FINGER_PINKY_2_R,
			BONE_FINGER_INDEX_META_R,
			BONE_FINGER_INDEX_0_R,
			BONE_FINGER_INDEX_1_R,
			BONE_FINGER_INDEX_2_R,
			BONE_FINGER_THUMB_0_R,
			BONE_FINGER_THUMB_1_R,
			BONE_FINGER_THUMB_2_R,
			BONE_FINGER_RING_META_R,
			BONE_FINGER_RING_0_R,
			BONE_FINGER_RING_1_R,
			BONE_FINGER_RING_2_R,
			BONE_WEAPON_HAND_R,
			BONE_ARM_LOWER_R_TWIST,
			BONE_ARM_LOWER_R_TWIST1,
			BONE_ARM_UPPER_R_TWIST,
			BONE_ARM_UPPER_R_TWIST1,
			BONE_LEG_UPPER_L,
			BONE_LEG_LOWER_L,
			BONE_ANKLE_L,
			BONE_BALL_L,
			BONE_LFOOT_LOCK,
			BONE_LEG_UPPER_L_TWIST,
			BONE_LEG_UPPER_L_TWIST1,
			BONE_LEG_UPPER_R,
			BONE_LEG_LOWER_R,
			BONE_ANKLE_R,
			BONE_BALL_R,
			BONE_RFOOT_LOCK,
			BONE_LEG_UPPER_R_TWIST,
			BONE_LEG_UPPER_R_TWIST1,
			BONE_FINGER_PINKY_L_END,
			BONE_FINGER_PINKY_R_END,
			BONE_VALVEBIPED_WEAPON_BONE,
			BONE_LH_IK_DRIVER,
			BONE_PRIMARY_JIGGLE_JNT,
		};

		enum game_type : int
		{
			GAMETYPE_UNKNOWN = -1,
			GAMETYPE_CLASSIC,
			GAMETYPE_GUNGAME,
			GAMETYPE_TRAINING,
			GAMETYPE_CUSTOM,
			GAMETYPE_COOPERATIVE,
			GAMETYPE_SKIRMISH,
			GAMETYPE_FREEFORALL
		};

		enum class EClassIndex : int
		{
			CAI_BaseNPC = 0,
			CAK47,
			CBaseAnimating,
			CBaseAnimatingOverlay,
			CBaseAttributableItem,
			CBaseButton,
			CBaseCombatCharacter,
			CBaseCombatWeapon,
			CBaseCSGrenade,
			CBaseCSGrenadeProjectile,
			CBaseDoor,
			CBaseEntity,
			CBaseFlex,
			CBaseGrenade,
			CBaseParticleEntity,
			CBasePlayer,
			CBasePropDoor,
			CBaseTeamObjectiveResource,
			CBaseTempEntity,
			CBaseToggle,
			CBaseTrigger,
			CBaseViewModel,
			CBaseVPhysicsTrigger,
			CBaseWeaponWorldModel,
			CBeam,
			CBeamSpotlight,
			CBoneFollower,
			CBRC4Target,
			CBreachCharge,
			CBreachChargeProjectile,
			CBreakableProp,
			CBreakableSurface,
			CBumpMine,
			CBumpMineProjectile,
			CC4,
			CCascadeLight,
			CChicken,
			CColorCorrection,
			CColorCorrectionVolume,
			CCSGameRulesProxy,
			CCSPlayer,
			CCSPlayerResource,
			CCSRagdoll,
			CCSTeam,
			CDangerZone,
			CDangerZoneController,
			CDEagle,
			CDecoyGrenade,
			CDecoyProjectile,
			CDrone,
			CDronegun,
			CDynamicLight,
			CDynamicProp,
			CEconEntity,
			CEconWearable,
			CEmbers,
			CEntityDissolve,
			CEntityFlame,
			CEntityFreezing,
			CEntityParticleTrail,
			CEnvAmbientLight,
			CEnvDetailController,
			CEnvDOFController,
			CEnvGasCanister,
			CEnvParticleScript,
			CEnvProjectedTexture,
			CEnvQuadraticBeam,
			CEnvScreenEffect,
			CEnvScreenOverlay,
			CEnvTonemapController,
			CEnvWind,
			CFEPlayerDecal,
			CFireCrackerBlast,
			CFireSmoke,
			CFireTrail,
			CFish,
			CFists,
			CFlashbang,
			CFogController,
			CFootstepControl,
			CFunc_Dust,
			CFunc_LOD,
			CFuncAreaPortalWindow,
			CFuncBrush,
			CFuncConveyor,
			CFuncLadder,
			CFuncMonitor,
			CFuncMoveLinear,
			CFuncOccluder,
			CFuncReflectiveGlass,
			CFuncRotating,
			CFuncSmokeVolume,
			CFuncTrackTrain,
			CGameRulesProxy,
			CGrassBurn,
			CHandleTest,
			CHEGrenade,
			CHostage,
			CHostageCarriableProp,
			CIncendiaryGrenade,
			CInferno,
			CInfoLadderDismount,
			CInfoMapRegion,
			CInfoOverlayAccessor,
			CItem_Healthshot,
			CItemCash,
			CItemDogtags,
			CKnife,
			CKnifeGG,
			CLightGlow,
			CMapVetoPickController,
			CMaterialModifyControl,
			CMelee,
			CMolotovGrenade,
			CMolotovProjectile,
			CMovieDisplay,
			CParadropChopper,
			CParticleFire,
			CParticlePerformanceMonitor,
			CParticleSystem,
			CPhysBox,
			CPhysBoxMultiplayer,
			CPhysicsProp,
			CPhysicsPropMultiplayer,
			CPhysMagnet,
			CPhysPropAmmoBox,
			CPhysPropLootCrate,
			CPhysPropRadarJammer,
			CPhysPropWeaponUpgrade,
			CPlantedC4,
			CPlasma,
			CPlayerPing,
			CPlayerResource,
			CPointCamera,
			CPointCommentaryNode,
			CPointWorldText,
			CPoseController,
			CPostProcessController,
			CPrecipitation,
			CPrecipitationBlocker,
			CPredictedViewModel,
			CProp_Hallucination,
			CPropCounter,
			CPropDoorRotating,
			CPropJeep,
			CPropVehicleDriveable,
			CRagdollManager,
			CRagdollProp,
			CRagdollPropAttached,
			CRopeKeyframe,
			CSCAR17,
			CSceneEntity,
			CSensorGrenade,
			CSensorGrenadeProjectile,
			CShadowControl,
			CSlideshowDisplay,
			CSmokeGrenade,
			CSmokeGrenadeProjectile,
			CSmokeStack,
			CSnowball,
			CSnowballPile,
			CSnowballProjectile,
			CSpatialEntity,
			CSpotlightEnd,
			CSprite,
			CSpriteOriented,
			CSpriteTrail,
			CStatueProp,
			CSteamJet,
			CSun,
			CSunlightShadowControl,
			CSurvivalSpawnChopper,
			CTablet,
			CTeam,
			CTeamplayRoundBasedRulesProxy,
			CTEArmorRicochet,
			CTEBaseBeam,
			CTEBeamEntPoint,
			CTEBeamEnts,
			CTEBeamFollow,
			CTEBeamLaser,
			CTEBeamPoints,
			CTEBeamRing,
			CTEBeamRingPoint,
			CTEBeamSpline,
			CTEBloodSprite,
			CTEBloodStream,
			CTEBreakModel,
			CTEBSPDecal,
			CTEBubbles,
			CTEBubbleTrail,
			CTEClientProjectile,
			CTEDecal,
			CTEDust,
			CTEDynamicLight,
			CTEEffectDispatch,
			CTEEnergySplash,
			CTEExplosion,
			CTEFireBullets,
			CTEFizz,
			CTEFootprintDecal,
			CTEFoundryHelpers,
			CTEGaussExplosion,
			CTEGlowSprite,
			CTEImpact,
			CTEKillPlayerAttachments,
			CTELargeFunnel,
			CTEMetalSparks,
			CTEMuzzleFlash,
			CTEParticleSystem,
			CTEPhysicsProp,
			CTEPlantBomb,
			CTEPlayerAnimEvent,
			CTEPlayerDecal,
			CTEProjectedDecal,
			CTERadioIcon,
			CTEShatterSurface,
			CTEShowLine,
			CTesla,
			CTESmoke,
			CTESparks,
			CTESprite,
			CTESpriteSpray,
			CTest_ProxyToggle_Networkable,
			CTestTraceline,
			CTEWorldDecal,
			CTriggerPlayerMovement,
			CTriggerSoundOperator,
			CVGuiScreen,
			CVoteController,
			CWaterBullet,
			CWaterLODControl,
			CWeaponAug,
			CWeaponAWP,
			CWeaponBaseItem,
			CWeaponBizon,
			CWeaponCSBase,
			CWeaponCSBaseGun,
			CWeaponCycler,
			CWeaponElite,
			CWeaponFamas,
			CWeaponFiveSeven,
			CWeaponG3SG1,
			CWeaponGalil,
			CWeaponGalilAR,
			CWeaponGlock,
			CWeaponHKP2000,
			CWeaponM249,
			CWeaponM3,
			CWeaponM4A1,
			CWeaponMAC10,
			CWeaponMag7,
			CWeaponMP5Navy,
			CWeaponMP7,
			CWeaponMP9,
			CWeaponNegev,
			CWeaponNOVA,
			CWeaponP228,
			CWeaponP250,
			CWeaponP90,
			CWeaponSawedoff,
			CWeaponSCAR20,
			CWeaponScout,
			CWeaponSG550,
			CWeaponSG552,
			CWeaponSG556,
			CWeaponShield,
			CWeaponSSG08,
			CWeaponTaser,
			CWeaponTec9,
			CWeaponTMP,
			CWeaponUMP45,
			CWeaponUSP,
			CWeaponXM1014,
			CWeaponZoneRepulsor,
			CWorld,
			CWorldVguiText,
			DustTrail,
			MovieExplosion,
			ParticleSmokeGrenade,
			RocketTrail,
			SmokeTrail,
			SporeExplosion,
			SporeTrail,
		};

		enum item_definitions : short
		{
			WEAPON_NONE = 0,
			WEAPON_DEAGLE = 1,
			WEAPON_ELITE = 2,
			WEAPON_FIVESEVEN = 3,
			WEAPON_GLOCK = 4,
			WEAPON_AK47 = 7,
			WEAPON_AUG = 8,
			WEAPON_AWP = 9,
			WEAPON_FAMAS = 10,
			WEAPON_G3SG1 = 11,
			WEAPON_GALILAR = 13,
			WEAPON_M249 = 14,
			WEAPON_M4A1 = 16,
			WEAPON_MAC10 = 17,
			WEAPON_P90 = 19,
			WEAPON_ZONE_REPULSOR = 20,
			WEAPON_MP5SD = 23,
			WEAPON_UMP45 = 24,
			WEAPON_XM1014 = 25,
			WEAPON_BIZON = 26,
			WEAPON_MAG7 = 27,
			WEAPON_NEGEV = 28,
			WEAPON_SAWEDOFF = 29,
			WEAPON_TEC9 = 30,
			WEAPON_TASER = 31,
			WEAPON_HKP2000 = 32,
			WEAPON_MP7 = 33,
			WEAPON_MP9 = 34,
			WEAPON_NOVA = 35,
			WEAPON_P250 = 36,
			WEAPON_SHIELD = 37,
			WEAPON_SCAR20 = 38,
			WEAPON_SG556 = 39,
			WEAPON_SSG08 = 40,
			WEAPON_KNIFE_GG = 41,
			WEAPON_KNIFE = 42,
			WEAPON_FLASHBANG = 43,
			WEAPON_HEGRENADE = 44,
			WEAPON_SMOKEGRENADE = 45,
			WEAPON_MOLOTOV = 46,
			WEAPON_DECOY = 47,
			WEAPON_INCGRENADE = 48,
			WEAPON_C4 = 49,
			WEAPON_HEALTHSHOT = 57,
			WEAPON_KNIFE_T = 59,
			WEAPON_M4A1_SILENCER = 60,
			WEAPON_USP_SILENCER = 61,
			WEAPON_CZ75A = 63,
			WEAPON_REVOLVER = 64,
			WEAPON_TAGRENADE = 68,
			WEAPON_FISTS = 69,
			WEAPON_BREACHCHARGE = 70,
			WEAPON_TABLET = 72,
			WEAPON_MELEE = 74,
			WEAPON_AXE = 75,
			WEAPON_HAMMER = 76,
			WEAPON_SPANNER = 78,
			WEAPON_KNIFE_GHOST = 80,
			WEAPON_FIREBOMB = 81,
			WEAPON_DIVERSION = 82,
			WEAPON_FRAG_GRENADE = 83,
			WEAPON_SNOWBALL = 84,
			WEAPON_BUMPMINE = 85,
			WEAPON_KNIFE_BAYONET = 500,
			WEAPON_KNIFE_CSS = 503,
			WEAPON_KNIFE_FLIP = 505,
			WEAPON_KNIFE_GUT = 506,
			WEAPON_KNIFE_KARAMBIT = 507,
			WEAPON_KNIFE_M9_BAYONET = 508,
			WEAPON_KNIFE_TACTICAL = 509,
			WEAPON_KNIFE_FALCHION = 512,
			WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
			WEAPON_KNIFE_BUTTERFLY = 515,
			WEAPON_KNIFE_PUSH = 516,
			WEAPON_KNIFE_CORD = 517,
			WEAPON_KNIFE_CANIS = 518,
			WEAPON_KNIFE_URSUS = 519,
			WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
			WEAPON_KNIFE_OUTDOOR = 521,
			WEAPON_KNIFE_STILETTO = 522,
			WEAPON_KNIFE_WIDOWMAKER = 523,
			WEAPON_KNIFE_SKELETON = 525,
			GLOVE_STUDDED_BROKENFANG = 4725,
			GLOVE_STUDDED_BLOODHOUND = 5027,
			GLOVE_T = 5028,
			GLOVE_CT = 5029,
			GLOVE_SPORTY = 5030,
			GLOVE_SLICK = 5031,
			GLOVE_LEATHER_HANDWRAPS = 5032,
			GLOVE_MOTORCYCLE = 5033,
			GLOVE_SPECIALIST = 5034,
			GLOVE_STUDDED_HYDRA = 5035,
			SPECIAL_AGENT_BLUEBERRIES_BUCKSHOT = 4619,
			SPECIAL_AGENT_TWO_TIMES_MCCOY_TACP = 4680,
			SPECIAL_AGENT_COMMANDOR_MAE_JAMISON = 4711,
			SPECIAL_AGENT_1ST_LIEUTENANT_FARLOW,
			SPECIAL_AGENT_JOHN_KASK,
			SPECIAL_AGENT_BIO_HAZ_SPECIALIST,
			SPECIAL_AGENT_SERGEANT_BOMBSON,
			SPECIAL_AGENT_CHEM_HAZ_SPECIALIST,
			SPECIAL_AGENT_REZAN_THE_REDSHIRT = 4718,
			SPECIAL_AGENT_SIR_BLOODY_MIAMI_DARRYL = 4726,
			SPECIAL_AGENT_SAFECRACKER_VOLTZMANN,
			SPECIAL_AGENT_LITTLE_KEV,
			SPECIAL_AGENT_GETAWAY_SALLY = 4730,
			SPECIAL_AGENT_NUMBER_K = 4732,
			SPECIAL_AGENT_SIR_BLOODY_SILENT_DARRYL = 4733,
			SPECIAL_AGENT_SIR_BLOODY_SKULLHEAD_DARRYL,
			SPECIAL_AGENT_SIR_BLOODY_DARRYL_ROYALE,
			SPECIAL_AGENT_SIR_BLOODY_LOUDMOUTH_DARRYL,
			SPECIAL_AGENT_T = 5036,
			SPECIAL_AGENT_CT = 5037,
			SPECIAL_AGENT_GROUND_REBEL = 5105,
			SPECIAL_AGENT_OSIRIS,
			SPECIAL_AGENT_SHAHMAT,
			SPECIAL_AGENT_MUHLIK,
			SPECIAL_AGENT_SOLDIER = 5205,
			SPECIAL_AGENT_ENFORCER,
			SPECIAL_AGENT_SLINGSHOT,
			SPECIAL_AGENT_STREET_SOLDIER,
			SPECIAL_AGENT_OPERATOR = 5305,
			SPECIAL_AGENT_MARKUS_DELROW,
			SPECIAL_AGENT_MICHAEL_SYFERS,
			SPECIAL_AGENT_AVA,
			SPECIAL_AGENT_3RD_COMMANDO_COMPANY = 5400,
			SPECIAL_AGENT_SEAL_TEAM_6_SOLDIER,
			SPECIAL_AGENT_BUCKSHOT,
			SPECIAL_AGENT_TWO_TIMES_MCCOY_USAF,
			SPECIAL_AGENT_RICKSAW,
			SPECIAL_AGENT_DRAGOMIR = 5500,
			SPECIAL_AGENT_MAXIMUS,
			SPECIAL_AGENT_REZAN_THE_READY,
			SPECIAL_AGENT_BLACKWOLF = 5503,
			SPECIAL_AGENT_THE_DOCTOR,
			SPECIAL_AGENT_DRAGOMIR_FOOTSOLDIERS,
			SPECIAL_AGENT_B_SQUADRON_OFFICER = 5601
		};
	}
}

#pragma region clientmode_definitions
#define SIGNONSTATE_NONE		0	// no state yet, about to connect
#define SIGNONSTATE_CHALLENGE	1	// client challenging server, all OOB packets
#define SIGNONSTATE_CONNECTED	2	// client is connected to server, netchans ready
#define SIGNONSTATE_NEW			3	// just got serverinfo and string tables
#define SIGNONSTATE_PRESPAWN	4	// received signon buffers
#define SIGNONSTATE_SPAWN		5	// ready to receive entity packets
#define SIGNONSTATE_FULL		6	// we are fully connected, first non-delta packet received (in-game check)
#define SIGNONSTATE_CHANGELEVEL	7	// server is changing level, please wait
#pragma endregion