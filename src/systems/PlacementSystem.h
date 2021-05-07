#pragma once
#include <protegon.h>
#include "core/Hell.h"
#include "components/Components.h"
#include "factories/Factories.h"

class PlacementSystem : public ecs::UESystem<PlayerInputComponent, InventoryComponent2, TransformComponent, RangeComponent, ShapeComponent> {
public:
	void Update() override {
		auto [entity, input, inventory, transform, range, shape] = GetEntityAndComponents();
		if (engine::InputHandler::KeyPressed(Key::C)) {
			auto& placement = entity.AddComponent<PlacementComponent>();
			auto mouse_position = engine::InputHandler::GetMousePosition();
			if (DistanceSquared(mouse_position, transform.transform.position) < range.range * range.range) {
				V2_int scaled_quantum = 8 * Hell::GetScale();
				mouse_position -= scaled_quantum / 2;
				V2_int placement_position = { 
					mouse_position.x - mouse_position.x % scaled_quantum.x,
					mouse_position.y - mouse_position.y % scaled_quantum.y
				};
				auto size = V2_int{ 16, 16 } * Hell::GetScale();
				placement.size = size;
				placement.position = placement_position;
				auto selected_item = Hasher::HashCString("grass");
				if (engine::InputHandler::MousePressed(MouseButton::RIGHT) && inventory.Has(selected_item)) {
					CreateGrass(GetManager(), placement_position);
					inventory.Remove(selected_item);
				}
			}
		} else {
			if (entity.HasComponent<PlacementComponent>()) {
				entity.RemoveComponent<PlacementComponent>();
			}
		}
	}
};

class PlacementRenderSystem : public ecs::UESystem<PlayerInputComponent> {
public:
	void Update() override {
		auto [entity, input] = GetEntityAndComponents();
		if (entity.HasComponent<PlacementComponent>()) {
			auto& placement = entity.GetComponent<PlacementComponent>();
			engine::Renderer::DrawRectangle(placement.position, placement.size, placement.color);
		}
	}
};