#pragma once
#include <protegon.h>
#include "components/Components.h"

class AIMovementSystem : public ecs::System<AIMovementComponent, Transform, RigidBody> {
public:
	void Update() override {
		for (auto [entity, ai, transform, rigid_body] : entities) {
			for (auto [player, transform2, player_input] : GetManager().GetEntityComponents<Transform, PlayerInputComponent>()) {
				auto speed = ai.speed;
				auto direction_vector = (transform2.position - transform.position).Normalized();
				rigid_body.velocity = speed * direction_vector;
				if (rigid_body.velocity.MagnitudeSquared() != 0) {
					transform.rotation = engine::math::PI<double> / 2 + std::atan2(rigid_body.velocity.y, rigid_body.velocity.x);
				}
			}
		}
	}
};