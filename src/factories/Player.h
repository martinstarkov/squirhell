#pragma once

#include <Protegon.h>

#include "factories/Bullet.h"

struct PlayerSpeed {
	PlayerSpeed(const V2_double& speed) : speed{ speed } {}
	V2_double speed;
};

struct GunComponent {
	GunComponent() = default;
	ptgn::Countdown reload;
};

inline ecs::Entity CreatePlayer(ecs::Manager& manager, const V2_double& position) {
	auto player{ manager.CreateEntity() };
	player.AddComponent<ptgn::TransformComponent>(ptgn::Transform{ position });
	player.AddComponent<ptgn::ShapeComponent>(ptgn::Circle{ 20 });
	player.AddComponent<ptgn::RigidBodyComponent>();
	player.AddComponent<ptgn::HitboxComponent>();
	player.AddComponent<ptgn::InputComponent>();
	player.AddComponent<ptgn::PlayerComponent>();
	player.AddComponent<ptgn::RenderComponent>();
	player.AddComponent<ptgn::ColorComponent>(ptgn::colors::BLUE);
	player.AddComponent<PlayerSpeed>(V2_double{ 5, 5 });
	auto& gun{ player.AddComponent<GunComponent>() };
	gun.reload = ptgn::Countdown(ptgn::milliseconds{ 0 });

	return player;
}

inline void DrawGun(ecs::Entity& player) {
	auto [transform, shape] = player.GetComponents<ptgn::TransformComponent, ptgn::ShapeComponent>();
	auto center{ shape.shape->GetCenter(transform.transform.position) };
	auto mouse_position{ ptgn::InputHandler::GetMousePosition() };
	auto direction{ mouse_position - center };
	auto destination{ center + direction.Normalized() * shape.shape->CastTo<ptgn::Circle>().radius };
	ptgn::ScreenRenderer::DrawLine(center, destination, ptgn::colors::WHITE);
}

inline void DrawPlayer(ecs::Entity& player) {
	DrawGun(player);
}

inline void PlayerShooting(ecs::Entity& player) {
	auto [transform, shape, gun] = player.GetComponents<ptgn::TransformComponent, ptgn::ShapeComponent, GunComponent>();
	auto center{ shape.shape->GetCenter(transform.transform.position) };
	bool activated{ ptgn::InputHandler::MousePressed(ptgn::Mouse::LEFT) };
	auto mouse_position{ ptgn::InputHandler::GetMousePosition() };
	auto direction{ mouse_position - center };
	if (activated && (gun.reload.Finished() || !gun.reload.IsRunning())) {
		auto bullet = CreateBullet(player.GetManager(), center);
		gun.reload.Start();
		player.GetManager().Refresh();
		auto& bullet_rigid_body{ bullet.GetComponent<ptgn::RigidBodyComponent>().body };
		bullet_rigid_body.velocity = direction.Normalized() * bullet.GetComponent<BulletProperties>().speed;
	}
}

inline void PlayerMovement(ecs::Entity& player) {
	// Read player inputs.
	auto [rigid_body, speed] = player.GetComponents<ptgn::RigidBodyComponent, PlayerSpeed>();
	bool w{ ptgn::InputHandler::KeyPressed(ptgn::Key::W) };
	bool a{ ptgn::InputHandler::KeyPressed(ptgn::Key::A) };
	bool s{ ptgn::InputHandler::KeyPressed(ptgn::Key::S) };
	bool d{ ptgn::InputHandler::KeyPressed(ptgn::Key::D) };
	if (a && !d) {
		rigid_body.body.velocity.x = -speed.speed.x;
	} else if (!a && d) {
		rigid_body.body.velocity.x = speed.speed.x;
	} else {
		rigid_body.body.velocity.x = 0;
	}
	if (w && !s) {
		rigid_body.body.velocity.y = -speed.speed.y;
	} else if (!w && s) {
		rigid_body.body.velocity.y = speed.speed.y;
	} else {
		rigid_body.body.velocity.y = 0;
	}
}

inline void UpdatePlayer(ecs::Entity& player) {
	PlayerMovement(player);
	PlayerShooting(player);
}