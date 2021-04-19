#pragma once
#include <protegon.h>
#include "components/TagComponents.h"

class MovementSystem : public ecs::System<PlayerInputComponent, TransformComponent, RigidBodyComponent>{
public:
	V2_double speed{ 3,3 };
	void Update() override {
		for (auto [entity, pic, tc, rbc] : entities) {
			if (engine::InputHandler::KeyPressed(Key::W) && engine::InputHandler::KeyReleased(Key::S)) {
				rbc.body->velocity.y = -speed.y;
			} else if (engine::InputHandler::KeyPressed(Key::S) && engine::InputHandler::KeyReleased(Key::W)) {
				rbc.body->velocity.y = speed.y;
			} else {
				rbc.body->velocity.y = 0;
			}

			if (engine::InputHandler::KeyPressed(Key::A) && engine::InputHandler::KeyReleased(Key::D)) {
				rbc.body->velocity.x = -speed.x;
			} else if (engine::InputHandler::KeyPressed(Key::D) && engine::InputHandler::KeyReleased(Key::A)) {
				rbc.body->velocity.x = speed.x;
			} else {
				rbc.body->velocity.x = 0;
			}
			if (rbc.body->velocity.MagnitudeSquared() != 0) {
				tc.rotation = engine::math::PI<double> / 2 + std::atan2(rbc.body->velocity.y, rbc.body->velocity.x);
			}
		}
	}
};
