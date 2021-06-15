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

		AdjustPlayerVelocity(player);
		
		// Static collision system.
		manager.ForEachEntityWith<ptgn::HitboxComponent, ptgn::TransformComponent, ptgn::ShapeComponent>(ptgn::StaticCollisionSystem{});

		manager.ForEachEntityWith<ptgn::LifetimeComponent>(ptgn::LifetimeSystem{});

		camera.CenterOn(player);

		chunk_manager.CenterOn(player.GetComponent<ptgn::TransformComponent>().transform.position, { 3, 3 });
		chunk_manager.Update();

		manager.Refresh();
	}
	ptgn::ChunkManager chunk_manager{ { 16, 16 }, { 16, 16 } };
	virtual void Render() override final {
		// Render system.
		manager.ForEachEntityWith<ptgn::TransformComponent, ptgn::ShapeComponent, ptgn::RenderComponent>(ptgn::DrawShapeSystem<ptgn::WorldRenderer>{});

		chunk_manager.Render();

		DrawPlayer(player);

		ptgn::WorldRenderer::DrawSolidRectangle({ 200, 200 }, { 70, 80 }, ptgn::colors::BLACK);
		ptgn::WorldRenderer::DrawSolidRectangle({ 400, 200 }, { 70, 80 }, ptgn::colors::BLACK);
		
		
	}
};