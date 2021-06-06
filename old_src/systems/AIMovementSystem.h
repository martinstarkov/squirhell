#pragma once

#include <Protegon.h>

#include "components/Components.h"

struct AIMovementSystem {
public:
	void operator()(ecs::Entity entity, 
					AIMovementComponent& ai, 
					ptgn::TransformComponent& transform, 
					ptgn::RigidBodyComponent& rigid_body) {
		entity.GetManager().ForEachEntityWith<ptgn::TransformComponent, ptgn::PlayerComponent>(
			[&](auto player, auto& transform2, auto& player_tag) {
			auto direction_vector{
				(transform2.transform.position - transform.transform.position).Normalized() };
			rigid_body.body.velocity = ai.speed * direction_vector;
			if (rigid_body.body.velocity.MagnitudeSquared() != 0) {
				auto velocity_angle{ std::atan2(rigid_body.body.velocity.y, rigid_body.body.velocity.x) };
				transform.transform.rotation = ptgn::math::PI<double> / 2.0 + velocity_angle;
			}
		});
	}
};