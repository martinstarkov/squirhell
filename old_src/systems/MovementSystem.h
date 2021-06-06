#pragma once

#include <protegon.h>
#include "components/Components.h"

using namespace engine;

class MovementSystem : public ecs::System<PlayerInputComponent, TransformComponent, RigidBodyComponent> {
public:
	V2_double speed{ 3,3 };
	void Update() override {
		for (auto [entity, player, transform, rigid_body] : entities) {
			if (InputHandler::KeyPressed(Key::W) &&
				InputHandler::KeyReleased(Key::S)) {
				rigid_body.body.velocity.y = -speed.y;
			} else if (InputHandler::KeyPressed(Key::S) &&
					   InputHandler::KeyReleased(Key::W)) {
				rigid_body.body.velocity.y = speed.y;
			} else {
				rigid_body.body.velocity.y = 0;
			}

			if (InputHandler::KeyPressed(Key::A) &&
				InputHandler::KeyReleased(Key::D)) {
				rigid_body.body.velocity.x = -speed.x;
			} else if (InputHandler::KeyPressed(Key::D) &&
					   InputHandler::KeyReleased(Key::A)) {
				rigid_body.body.velocity.x = speed.x;
			} else {
				rigid_body.body.velocity.x = 0;
			}
			//// Rotation based on player velocity
			//if (rigid_body.body.velocity.MagnitudeSquared() != 0) {
			//	transform.transform.rotation = engine::math::PI<double> / 2 + std::atan2(rigid_body.body.velocity.y, rigid_body.body.velocity.x);
			//}
			auto relative_vector = engine::InputHandler::GetMousePosition() - transform.transform.position;
			transform.transform.rotation = engine::math::PI<double> / 2 + std::atan2(relative_vector.y, relative_vector.x);
		}
	}
};
