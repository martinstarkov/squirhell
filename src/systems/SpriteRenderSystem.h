#pragma once

#include <protegon.h>

#include "components/Components.h"

#include "core/Hell.h"

using namespace engine;

class SpriteRenderSystem : public ecs::System<Transform, ShapeComponent, SpriteKeyComponent, HitboxComponent> {
public:
	void Update() override {
		for (auto [entity, transform, shape, sprite, hitbox] : entities) {
			auto size{ sprite.sprite_size * Hell::GetScale() };
			Renderer::DrawTexture(
				sprite.key,
				transform.position + hitbox.offset * Hell::GetScale() - size / 2.0,
				size,
				{}, {},
				nullptr,
				math::RadiansToDegrees(transform.rotation),
				Flip::NONE
			);
			Renderer::DrawCircle(
				transform.position,
				5 * Hell::GetScale().x,
				colors::BLUE
			);
		}
	}
};