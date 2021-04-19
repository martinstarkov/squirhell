#pragma once
#include <protegon.h>
#include "components/TagComponents.h"
#include "components/AIMovementComponent.h"

class AIMovementSystem : public ecs::System<AIMovementComponent, TransformComponent, RigidBodyComponent> {
public:
	void Update() override {
		for (auto [entity, ai, tc, rbc] : entities) {
			for (auto [player, transform, pic] : GetManager().GetEntityComponents<TransformComponent, PlayerInputComponent>()) {
				auto speed = ai.speed;
				auto direction_vector = (transform.position - tc.position).Normalized();
				rbc.body->velocity = speed * direction_vector;
				if (rbc.body->velocity.MagnitudeSquared() != 0) {
					tc.rotation = engine::math::PI<double> / 2 + std::atan2(rbc.body->velocity.y, rbc.body->velocity.x);
				}
			}
		}
	}
};