#pragma once

#include <protegon.h>

#include "components/Components.h"

class BulletRenderSystem : public ecs::System<BulletComponent, Transform, Color, RigidBody, ShapeComponent> {
public:
	void Update() override {
		for (auto [entity, bullet, transform, color, rigid_body, shape] : entities) {
			auto radius{ shape.shape->CastTo<Circle>().radius };
			Renderer::DrawSolidCircle(
				transform.position, 
				radius, 
				color
			);
		}
	}
};