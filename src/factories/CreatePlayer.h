#pragma once

#include <Protegon.h>

struct PlayerSpeed {
	PlayerSpeed(const V2_double& speed) : speed{ speed } {}
	V2_double speed;
};

inline ecs::Entity CreatePlayer(ecs::Manager& manager, const V2_double& position) {
	auto player{ manager.CreateEntity() };
	player.AddComponent<ptgn::TransformComponent>(ptgn::Transform{ position });
	player.AddComponent<PlayerSpeed>(V2_double{ 3, 3 });

	return player;
}