#pragma once

#include <Protegon.h>

#include "factories/Player.h"

class Level1 : public ptgn::Scene {
public:
	ecs::Entity player;
	virtual void Init() override final {
		player = CreatePlayer(manager, { 300, 300 });

		manager.Refresh();
	}
	virtual void Update() override final {
		UpdatePlayer(player);

		// Movement system.
		manager.ForEachEntityWith<ptgn::TransformComponent, ptgn::RigidBodyComponent>(ptgn::MovementSystem{});
		
		// Static collision system.
		manager.ForEachEntityWith<ptgn::HitboxComponent, ptgn::TransformComponent, ptgn::ShapeComponent>(ptgn::StaticCollisionSystem{});

		manager.ForEachEntityWith<ptgn::LifetimeComponent>(ptgn::LifetimeSystem{});

		manager.Refresh();
	}
	virtual void Render() override final {
		// Render system.
		manager.ForEachEntityWith<ptgn::TransformComponent, ptgn::ShapeComponent, ptgn::RenderComponent>(ptgn::DrawShapeSystem<ptgn::ScreenRenderer>{});

		DrawPlayer(player);
		
		
	}
};