#pragma once

#include <protegon.h>

#include "components/TagComponents.h"

class BulletRenderSystem : public ecs::System<BulletComponent, TransformComponent, RenderComponent, RigidBodyComponent> {
public:
	void Update() override {
		for (auto [entity, bc, tc, rc, rbc] : entities) {
			engine::TextureManager::DrawSolidCircle(tc.position, engine::math::Round(rbc.body->shape->GetRadius()), rc.color);
		}
	}
};