#pragma once

#include <Protegon.h>

#include "factories/Player.h"
#include "scenes/Level1Chunk.h"

inline constexpr std::uint32_t PLAYER_POSITION{ ptgn::Color::AsUint32(45,  255,  49, 255) };

class Level1 : public ptgn::Scene {
public:
	ecs::Entity player;
	virtual void Init() override final {
		ptgn::LevelManager::Load("level1", "resources/levels/level1_prototype.png");
		const ptgn::Level& level = ptgn::LevelManager::GetLevel("level1");
		player = CreatePlayer(manager, level.GetPosition(ptgn::Color::FromUint32(PLAYER_POSITION), chunk_manager.GetTileSize()));

		manager.Refresh();
	}
	virtual void Update() override final {
		UpdatePlayer(player);

		// Movement system.
		manager.ForEachEntityWith<ptgn::TransformComponent, ptgn::RigidBodyComponent>(ptgn::MovementSystem{});
		
		auto player_position = player.GetComponent<ptgn::TransformComponent>().transform.position;
		auto player_center = player.GetComponent<ptgn::ShapeComponent>().shape->GetCenter(player_position);
		camera.CenterOn(player_center);

		chunk_manager.UpdateChunks<Level1Chunk>();

		AdjustPlayerVelocity(player);

		chunk_manager.Update();
		
		chunk_manager.ResolveCollisionsWith(player);
		
		manager.ForEachEntityWith<BulletProperties>([&](auto bullet, auto& properties) {
			chunk_manager.ResolveCollisionsWith(bullet);
		});
		
		// Static collision system.
		manager.ForEachEntityWith<ptgn::HitboxComponent, ptgn::TransformComponent, ptgn::ShapeComponent>(ptgn::StaticCollisionSystem{});

		manager.ForEachEntityWith<ptgn::LifetimeComponent>(ptgn::LifetimeSystem{});

		chunk_manager.CenterOn(player_center);

		manager.Refresh();
	}
	ptgn::ChunkManager chunk_manager{ { 16, 16 }, { 16, 16 }, { 9, 9 }, { 7, 7 }, { 5, 5 } };
	virtual void Render() override final {
		// Render system.
		manager.ForEachEntityWith<ptgn::TransformComponent, ptgn::ShapeComponent, ptgn::RenderComponent>(ptgn::DrawShapeSystem<ptgn::WorldRenderer>{});

		chunk_manager.Render();

		DrawPlayer(player);

		ptgn::WorldRenderer::DrawSolidRectangle({ 200, 200 }, { 70, 80 }, ptgn::colors::BLACK);
		ptgn::WorldRenderer::DrawSolidRectangle({ 400, 200 }, { 70, 80 }, ptgn::colors::BLACK);
		
		
	}
};