#pragma once
#include <protegon.h>
#include "components/Components.h"

class AIMovementSystem : public ecs::System<AIMovementComponent, TransformComponent, RigidBodyComponent> {
public:
	void Update() override {
		for (auto [entity, ai, transform, rigid_body] : entities) {
			for (auto [player, transform2, player_input] : GetManager().GetEntitiesAndComponents<TransformComponent, PlayerInputComponent>()) {
				auto speed = ai.speed;
				auto direction_vector = (transform2.transform.position - transform.transform.position).Normalized();
				rigid_body.body.velocity = speed * direction_vector;
				if (rigid_body.body.velocity.MagnitudeSquared() != 0) {
					transform.transform.rotation = engine::math::PI<double> / 2 + std::atan2(rigid_body.body.velocity.y, rigid_body.body.velocity.x);
				}
			}
		}
	}
};