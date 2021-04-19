#pragma once
#include <protegon.h>

class RigidBodySystem : public ecs::System<Transform, RigidBody> {
public:
	void Update() override {
		for (auto [entity, transform, rigid_body] : entities) {
			transform.position += rigid_body.velocity;
		}
	}
};
