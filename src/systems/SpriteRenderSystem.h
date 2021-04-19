#pragma once

#include <protegon.h>

#include "components/Components.h"

#include "core/Hell.h"

using namespace engine;

class SpriteRenderSystem : public ecs::System<Transform, ShapeComponent> {
public:
	void Update() override {
		for (auto [entity, transform, shape] : entities) {
			switch (shape.shape->GetType()) {
				case ShapeType::CIRCLE: {
					Renderer::DrawCircle(
						transform.position,
						shape.shape->CastTo<Circle>().radius,
						colors::BLUE
					);
					break;
				}
				case ShapeType::AABB: {
					auto size{ shape.shape->CastTo<AABB>().size };
					if (entity.HasComponent<SpriteKeyComponent>()) {
						auto& sprite{ entity.GetComponent<SpriteKeyComponent>() };
						Renderer::DrawTexture(
							sprite.key,
							transform.position,
							size * Hell::GetScale(),
							{}, {},
							nullptr,
							math::RadiansToDegrees(transform.rotation),
							Flip::NONE,
						);
					} else {
						Renderer::DrawRectangle(
							transform.position,
							size,
							colors::RED
						);
					}
					break;
				}
			}
		}
	}
};