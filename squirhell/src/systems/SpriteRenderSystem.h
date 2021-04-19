#pragma once

#include <protegon.h>

#include "components/SpriteKeyComponent.h"

#include "core/Hell.h"

class SpriteRenderSystem : public ecs::System<TransformComponent, SizeComponent, SpriteKeyComponent> {
public:
	void Update() override {
		for (auto [entity, tc, sc, sprite] : entities) {
			engine::TextureManager::DrawRectangle(sprite.key, { 0,0 }, sc.size, tc.position, sc.size * Hell::GetScale(), Flip::NONE, nullptr, engine::math::RadiansToDegrees(tc.rotation));
		}
	}
};