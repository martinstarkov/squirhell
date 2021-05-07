#pragma once

#include <protegon.h>
#include "components/Components.h"
#include "core/Hell.h"
using namespace engine;

class InventorySystem : public ecs::UESystem<PlayerInputComponent, InventoryComponent> {
public:
	void Update() {
		auto [entity, player, inventory] = GetEntityAndComponents();
		for (auto& pair : inventory.inventory) {
			auto id = pair.first;
			auto item = pair.second.first;
			auto count = pair.second.second;
		}
	}
};