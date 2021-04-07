#pragma once
#include <protegon.h>

class RigidBodySystem : public ecs::System<TransformComponent, RigidBodyComponent> {
public:
	void Update() override {
		for (auto [entity, tc, rbc] : entities) {
			tc.position += rbc.body->velocity;
		}
	}
};
