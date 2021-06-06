#pragma once

#include <Protegon.h>

struct BulletProperties {
	BulletProperties() = default;
	V2_double speed;
};

inline ecs::Entity CreateBullet(ecs::Manager& manager, const V2_double& position) {
	auto bullet{ manager.CreateEntity() };
	bullet.AddComponent<ptgn::TransformComponent>(ptgn::Transform{ position });
	bullet.AddComponent<ptgn::ShapeComponent>(ptgn::Circle{ 5 });
	bullet.AddComponent<ptgn::RigidBodyComponent>();
	bullet.AddComponent<ptgn::HitboxComponent>();
	bullet.AddComponent<ptgn::RenderComponent>();
	bullet.AddComponent<ptgn::ColorComponent>(ptgn::colors::GREY);
	bullet.AddComponent<ptgn::LifetimeComponent>(ptgn::seconds{ 1 });
	auto& properties{ bullet.AddComponent<BulletProperties>() };
	properties.speed = { 30, 30 };

	return bullet;
}