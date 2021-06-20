#pragma once

#include <Protegon.h>

#include "factories/Bullet.h"
#include "factories/CutsceneBlock.h"

struct PlayerProperties {
	PlayerProperties() = delete;
	PlayerProperties(const V2_double& acceleration,
					 const V2_double& terminal_velocity) : 
		acceleration{ acceleration },
		terminal_velocity{ terminal_velocity } {}
	V2_double acceleration;
	V2_double terminal_velocity;
};

struct GunComponent {
	GunComponent() = default;
	ptgn::Countdown reload;
	bool automatic{ true };
};

inline void PlayerCollision(ecs::Entity& player, ecs::Entity& collision_entity, const ptgn::Manifold& manifold) {
	if (collision_entity.HasComponent<CutsceneTrigger>()) {
		auto& cutscene = collision_entity.GetComponent<CutsceneTrigger>();
		if (!cutscene.complete) {
			cutscene.Update(player);
		} else {
			auto& manager = collision_entity.GetManager();
			collision_entity.Destroy();
			manager.Refresh();
		}
	} else {
		assert(player.HasComponent<ptgn::TransformComponent>());
		player.GetComponent<ptgn::TransformComponent>().transform.position -= manifold.penetration;
	}
}

inline ecs::Entity CreatePlayer(ecs::Manager& manager, const V2_double& position) {
	auto player{ manager.CreateEntity() };
	player.AddComponent<ptgn::TransformComponent>(ptgn::Transform{ position });
	player.AddComponent<ptgn::ShapeComponent>(ptgn::Circle{ 8 });
	player.AddComponent<ptgn::RigidBodyComponent>();
	auto& hitbox = player.AddComponent<ptgn::HitboxComponent>();
	hitbox.resolution_function = &PlayerCollision;
	hitbox.ignored_tags.emplace(ptgn::math::Hash("bullet"));
	player.AddComponent<ptgn::InputComponent>();
	player.AddComponent<ptgn::PlayerComponent>();
	player.AddComponent<ptgn::TagComponent>(ptgn::math::Hash("player"));
	player.AddComponent<ptgn::RenderComponent>();
	player.AddComponent<ptgn::ColorComponent>(ptgn::colors::BLUE);
	player.AddComponent<PlayerProperties>(V2_double{ 1.0, 1.0 }, V2_double{ 2, 2 });
	auto& gun{ player.AddComponent<GunComponent>() };
	gun.reload = ptgn::Countdown(ptgn::milliseconds{ 200 });
	gun.automatic = false;

	return player;
}

inline void AdjustPlayerVelocity(ecs::Entity& player) {
	if (player.HasComponents<ptgn::RigidBodyComponent, PlayerProperties>()) {
		auto [rigid_body, properties] = player.GetComponents<ptgn::RigidBodyComponent, PlayerProperties>();
		auto& velocity{ rigid_body.body.velocity };
		velocity *= 0.9;
		velocity = ptgn::math::Clamp(velocity, -properties.terminal_velocity, properties.terminal_velocity);
	}
}

inline void DrawGun(ecs::Entity& player) {
	assert((player.HasComponents<ptgn::TransformComponent, ptgn::ShapeComponent>()));
	auto [transform, shape] = player.GetComponents<ptgn::TransformComponent, ptgn::ShapeComponent>();
	auto center{ shape.shape->GetCenter(transform.transform.position) };
	auto mouse_position{ ptgn::InputHandler::GetMouseWorldPosition() };
	auto direction{ mouse_position - center };
	auto destination{ center + direction.Normalized() * shape.shape->CastTo<ptgn::Circle>().radius };
	ptgn::WorldRenderer::DrawLine(center, destination, ptgn::colors::WHITE);
}

inline void DrawPlayer(ecs::Entity& player) {
	DrawGun(player);
}

inline void PlayerShooting(ecs::Entity& player) {
	if (player.HasComponents<ptgn::TransformComponent, ptgn::ShapeComponent, GunComponent, ptgn::RigidBodyComponent>()) {
		auto [transform, shape, gun, rigid_body] = player.GetComponents<ptgn::TransformComponent, ptgn::ShapeComponent, GunComponent, ptgn::RigidBodyComponent>();
		auto center{ shape.shape->GetCenter(transform.transform.position) };
		bool activated = false;
		if (gun.automatic) {
			activated = ptgn::InputHandler::MousePressed(ptgn::Mouse::LEFT);
		} else {
			activated = ptgn::InputHandler::MouseDown(ptgn::Mouse::LEFT);
		}
		auto mouse_position{ ptgn::InputHandler::GetMouseWorldPosition() };
		auto direction{ mouse_position - center };
		if (activated && (gun.reload.Finished() || !gun.reload.IsRunning())) {
			auto bullet = CreateBullet(player.GetManager(), center);
			gun.reload.Start();
			player.GetManager().Refresh();
			assert(bullet.HasComponent<ptgn::RigidBodyComponent>());
			assert(bullet.HasComponent<BulletProperties>());
			auto& bullet_rigid_body{ bullet.GetComponent<ptgn::RigidBodyComponent>().body };
			bullet_rigid_body.velocity = rigid_body.body.velocity + direction.Normalized() * bullet.GetComponent<BulletProperties>().speed;
		}
	}
}

inline void PlayerMovement(ecs::Entity& player) {
	if (player.HasComponents<ptgn::RigidBodyComponent, PlayerProperties>()) {
		auto [rigid_body, properties] = player.GetComponents<ptgn::RigidBodyComponent, PlayerProperties>();
		// Read player inputs.
		bool w{ ptgn::InputHandler::KeyPressed(ptgn::Key::W) };
		bool a{ ptgn::InputHandler::KeyPressed(ptgn::Key::A) };
		bool s{ ptgn::InputHandler::KeyPressed(ptgn::Key::S) };
		bool d{ ptgn::InputHandler::KeyPressed(ptgn::Key::D) };
		auto& acceleration{ rigid_body.body.acceleration };
		if (a && !d) {
			acceleration.x = -properties.acceleration.x;
		} else if (!a && d) {
			acceleration.x = properties.acceleration.x;
		} else {
			acceleration.x = 0;
		}
		if (w && !s) {
			acceleration.y = -properties.acceleration.y;
		} else if (!w && s) {
			acceleration.y = properties.acceleration.y;
		} else {
			acceleration.y = 0;
		}
	}
}

inline void PlayerCamera(ecs::Entity& player) {
	auto& camera{ ptgn::SceneManager::GetActiveCamera() };
	if (ptgn::InputHandler::KeyPressed(ptgn::Key::Q)) {
		camera.ZoomOut();
	}
	if (ptgn::InputHandler::KeyPressed(ptgn::Key::E)) {
		camera.ZoomIn();
	}
}

inline void UpdatePlayer(ecs::Entity& player) {
	PlayerCamera(player);
	PlayerMovement(player);
	PlayerShooting(player);
}