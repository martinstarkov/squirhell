#pragma once
#include <protegon.h>

class RigidBodySystem : public ecs::System<TransformComponent, RigidBodyComponent> {
public:
	void Update() override {
		for (auto [entity, transform, rigid_body] : entities) {
			transform.transform.position += rigid_body.body.velocity;
		}
	}
};
