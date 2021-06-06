#pragma once

#include <Protegon.h>

#include "factories/CreatePlayer.h"

class Level1 : public ptgn::Scene {
public:
	ecs::Entity player;
	virtual void Init() override final {
		player = CreatePlayer(manager, { 300, 300 });
	}
	virtual void Update() override final {
		// Movemenet input system.
		manager.ForEachEntityWith<ptgn::RigidBodyComponent, ptgn::InputComponent, ptgn::PlayerComponent, PlayerSpeed>(
			[](ecs::Entity entity, ptgn::RigidBodyComponent& rigid_body, auto& input, auto& player, auto& speed_component) {
			bool w{ ptgn::InputHandler::KeyPressed(ptgn::Key::W) };
			bool a{ ptgn::InputHandler::KeyPressed(ptgn::Key::A) };
			bool s{ ptgn::InputHandler::KeyPressed(ptgn::Key::S) };
			bool d{ ptgn::InputHandler::KeyPressed(ptgn::Key::D) };
			if (a && !d) {
				rigid_body.body.velocity.x = -speed_component.speed.x;
			} else if (!a && d) {
				rigid_body.body.velocity.x = speed_component.speed.x;
			} else {
				rigid_body.body.velocity.x = 0;
			}
			if (w && !s) {
				rigid_body.body.velocity.y = -speed_component.speed.y;
			} else if (!w && s) {
				rigid_body.body.velocity.y = speed_component.speed.y;
			} else {
				rigid_body.body.velocity.y = 0;
			}
		});

		// Movement system.
		manager.ForEachEntityWith<ptgn::TransformComponent, ptgn::RigidBodyComponent>(
			[](ecs::Entity entity, ptgn::TransformComponent& transform, ptgn::RigidBodyComponent& rigid_body) {
			rigid_body.body.velocity += rigid_body.body.acceleration;
			rigid_body.body.angular_velocity += rigid_body.body.angular_acceleration;
			transform.transform.position += rigid_body.body.velocity;
			transform.transform.rotation += rigid_body.body.angular_velocity;
		});
		
		// Static collision system.
		manager.ForEachEntityWith<ptgn::HitboxComponent, ptgn::TransformComponent, ptgn::ShapeComponent>(ptgn::StaticCollisionSystem{});
	}
	virtual void Render() override final {
		// Render system.
		manager.ForEachEntityWith<ptgn::TransformComponent, ptgn::ShapeComponent, ptgn::RenderComponent>(ptgn::DrawSolidShapeSystem<ptgn::ScreenRenderer>{});
	}
};