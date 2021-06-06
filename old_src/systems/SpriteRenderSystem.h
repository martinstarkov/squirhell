#pragma once

#include <protegon.h>

#include "components/Components.h"

#include "core/Hell.h"

using namespace engine;

class SpriteRenderSystem : public ecs::System<TransformComponent, ShapeComponent, SpriteKeyComponent, HitboxComponent> {
public:
	void Update() override {
		for (auto [entity, transform, shape, sprite, hitbox] : entities) {
			auto size{ sprite.sprite_size * Hell::GetScale() };
			auto position = transform.transform.position;
			auto type = shape.shape->GetType();
			if (type == engine::ShapeType::CIRCLE) {
				position -= size / 2.0;
			}
			//V2_int center = V2_int{8,9} * Hell::GetScale();
			V2_int center = size/2.0 + hitbox.offset * Hell::GetScale();
			Renderer::DrawTexture(
				sprite.key,
				position - hitbox.offset * Hell::GetScale(),
				size,
				{}, {},
				&center,
				math::RadiansToDegrees(transform.transform.rotation),
				Flip::NONE
			);
			if (type == engine::ShapeType::CIRCLE) {
				Renderer::DrawCircle(
					transform.transform.position,
					5 * Hell::GetScale().x,
					colors::BLUE
				);
			} else if (type == engine::ShapeType::AABB) {
				Renderer::DrawRectangle(
					transform.transform.position,
					size,
					colors::BLUE
				);
			}
		}
	}
};