#pragma once

#include <Protegon.h>

#include "factories/CutsceneBlock.h"

inline constexpr std::uint32_t LEVEL_1_WALL                 { ptgn::colors::BLACK.ToUint32() };
inline constexpr std::uint32_t CUTSCENE_1_TRIGGER           { ptgn::Color::AsUint32(128, 128, 128, 255) };
inline constexpr std::uint32_t ROOM_1_ENEMY_POSITION        { ptgn::Color::AsUint32(178,   0, 255, 255) };
inline constexpr std::uint32_t CUTSCENE_1_FADING_WALL       { ptgn::Color::AsUint32(255, 237,  45, 255) };
inline constexpr std::uint32_t CUTSCENE_2_TRIGGER           { ptgn::Color::AsUint32(25,  189, 255, 255) };
inline constexpr std::uint32_t LEVEL_1_BOSS_POSITION        { ptgn::Color::AsUint32(255,   0,  16, 255) };

class Level1Chunk : public ptgn::Chunk {
public:
	virtual ~Level1Chunk() = default;

	virtual void Create() override {
		const ptgn::Level& level = ptgn::LevelManager::GetLevel("level1");
		auto level_size = level.GetSize();
		auto tiles = parent_->GetTilesPerChunk();
		auto tile_size = parent_->GetTileSize();
		ptgn::AABB tile{ tile_size };
		ptgn::Color invalid_color = ptgn::colors::WHITE;
		ptgn::Color color = invalid_color;
		//manager_.Reserve(tiles.x * tiles.y);
		auto chunk_position = coordinate_ * tiles;
		for (auto i{ 0 }; i < tiles.x; ++i) {
			for (auto j{ 0 }; j < tiles.y; ++j) {
				auto tile_position = chunk_position + V2_int{ i, j };
				color = level.GetColor(tile_position, invalid_color);
				if (color != invalid_color) {
					auto position = tile_position * tile_size;
					switch (color.ToUint32()) {
						case LEVEL_1_WALL: {
							auto entity = manager_.CreateEntity();
							entity.AddComponent<ptgn::TransformComponent>(ptgn::Transform{ position });
							entity.AddComponent<ptgn::ShapeComponent>(tile);
							entity.AddComponent<ptgn::RenderComponent>();
							entity.AddComponent<ptgn::ColorComponent>(color);
							entity.AddComponent<ptgn::HitboxComponent>();
							entity.AddComponent<ptgn::TagComponent>(ptgn::math::Hash("level1_wall"));
							break;
						}
						case CUTSCENE_1_TRIGGER: {
							auto entity = manager_.CreateEntity();
							CreateCutsceneTrigger<&Cutscene1>(entity, position, tile_size + V2_int{ tile_size.x * 13, 0 });
						}
					}
				}
			}
		}
		color = ptgn::colors::BLACK;
		manager_.Refresh();
	}

	virtual void Render() override {
		manager_.ForEachEntityWith<ptgn::TransformComponent, ptgn::ShapeComponent, ptgn::RenderComponent>(ptgn::DrawShapeSystem<ptgn::WorldRenderer>{});
		// Render chunk outlines.
		//auto chunk_size = parent_->GetChunkSize();
		//ptgn::DebugRenderer<ptgn::WorldRenderer>::DrawRctangle(coordinate_ * chunk_size, chunk_size, ptgn::colors::BLACK);
	}
};