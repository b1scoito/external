#pragma once

class c_client
{
public: // Read
	const auto get_local_player() const
	{
		auto local_player = g_memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwLocalPlayer);
		if (!local_player)
		{
			while (!local_player)
			{
				local_player = g_memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwLocalPlayer);
				timer::sleep(100);
			}
		}

		return local_player;
	}

	const auto in_menu() const
	{
		CURSORINFO ci{ sizeof(CURSORINFO) };
		if (!GetCursorInfo(&ci))
			return false;

		const auto handle = ci.hCursor;
		if ((handle > (HCURSOR)50000) && (handle < (HCURSOR)100000))
			return true;

		return false;
	}

	const auto get_game_type() const
	{
		const auto game_rules_proxy = g_memory->read<std::uintptr_t>(sdk::offsets::dwGameRulesProxy);
		const auto game_type = g_memory->read<std::int32_t>(game_rules_proxy + sdk::netvars::m_SurvivalGameRuleDecisionTypes);

		return game_type;
	}

	const auto get_glow_object_manager() const
	{
		return g_memory->read<std::uintptr_t>(sdk::base->get_client_image().base + sdk::offsets::dwGlowObjectManager);
	}

	const auto get_force_jump() const {
		return g_memory->read<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceJump);
	}

	const auto get_force_attack() const {
		return g_memory->read<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceAttack);
	}

public: // Write
	const auto force_jump(const std::int32_t state) const {
		return g_memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceJump, state);
	}

	const auto force_attack(const std::int32_t state) const {
		return g_memory->write<std::int32_t>(sdk::base->get_client_image().base + sdk::offsets::dwForceAttack, state);
	}
};

inline auto g_client = std::make_unique<c_client>();