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
			void*	pSaveData;					// 0x30
			bool	bClient;					// 0x34
			bool	bRemoteClient;				// 0x35
			int		iTimestampNetworkingBase;	// 0x36
			int		iTimestampRandomizeWindow;	// 0x3A
		}; // Size: 0x3E

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
			void set(const float red, const float green, const float blue, const float alpha, const int nRenderStyle = GLOWRENDERSTYLE_DEFAULT) // @note: styles not used cuz other styles doesnt have ignorez flag and needed to rebuild glow
			{
				this->R = red;
				this->G = green;
				this->B = blue;
				this->A = alpha;

				//this->flBloomAmount = 1.0f;
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
		enum entity_flags : int
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

		enum entity_move_type : int
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

		enum entity_team_id : int
		{
			TEAM_UNASSIGNED = 0,
			TEAM_SPECTATOR,
			TEAM_TT,
			TEAM_CT
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