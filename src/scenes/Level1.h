#pragma once

#include <Protegon.h>

#include "factories/Player.h"

class Level1 : public ptgn::Scene {
public:
	ecs::Entity player;
	virtual void Init() override final {
		ptgn::LevelManager::Load("level1", "resources/levels/level1.png");
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

		auto player_position = player.GetComponent<ptgn::TransformComponent>().transform.position;
		auto player_center = player.GetComponent<ptgn::ShapeComponent>().shape->GetCenter(player_position);

		chunk_manager.CenterOn(player_center);
		chunk_manager.Update();

		manager.Refresh();
	}
	ptgn::ChunkManager chunk_manager{ { 16, 16 }, { 16, 16 }, { 20, 20 }, { 3, 3 }, { 3, 3 } };
	virtual void Render() override final {
		// Render system.
		manager.ForEachEntityWith<ptgn::TransformComponent, ptgn::ShapeComponent, ptgn::RenderComponent>(ptgn::DrawShapeSystem<ptgn::WorldRenderer>{});

		chunk_manager.Render();

		DrawPlayer(player);

		ptgn::WorldRenderer::DrawSolidRectangle({ 200, 200 }, { 70, 80 }, ptgn::colors::BLACK);
		ptgn::WorldRenderer::DrawSolidRectangle({ 400, 200 }, { 70, 80 }, ptgn::colors::BLACK);
		
		
	}
};