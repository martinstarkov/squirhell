#pragma once

#include <Protegon.h>

struct BulletProperties {
	BulletProperties() = default;
	V2_double speed;
};

inline void BulletCollision(ecs::Entity& bullet, ecs::Entity& collision_entity, const ptgn::Manifold& manifold) {
	bullet.Destroy();
}

inline ecs::Entity CreateBullet(ecs::Manager& manager, const V2_double& position) {
	auto bullet{ manager.CreateEntity() };
	bullet.AddComponent<ptgn::TransformComponent>(ptgn::Transform{ position });
	bullet.AddComponent<ptgn::ShapeComponent>(ptgn::Circle{ 2 });
	bullet.AddComponent<ptgn::RigidBodyComponent>();
	auto& hitbox = bullet.AddComponent<ptgn::HitboxComponent>();
	hitbox.resolution_function = &BulletCollision;
	bullet.AddComponent<ptgn::RenderComponent>();
	bullet.AddComponent<ptgn::TagComponent>(ptgn::math::Hash("bullet"));
	bullet.AddComponent<ptgn::ColorComponent>(ptgn::colors::GREY);
	bullet.AddComponent<ptgn::LifetimeComponent>(ptgn::seconds{ 1 });
	auto& properties{ bullet.AddComponent<BulletProperties>() };
	properties.speed = { 10, 10 };

	return bullet;
}