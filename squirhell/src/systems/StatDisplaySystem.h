#pragma once

#include <protegon.h>

#include "components/TagComponents.h"
#include "components/AmmoComponent.h"
#include "components/HealthComponent.h"

#include "core/Hell.h"

class StatDisplaySystem : public ecs::System<PlayerInputComponent, AmmoComponent, HealthComponent> {
public:
	std::string ammo_title = "Ammo: ";
	std::string health_title = "Health: ";
	void Update() override {
		for (auto [entity, pic, ac, health] : entities) {
			//engine::TextureManager::DrawSolidRectangle(V2_int{ 20, 20 }, V2_int{ 2 * 10 + slot_size.x * inventory.tiles.size() + 10 * (inventory.tiles.size() - 1), 2 * 10 + slot_size.y }, { 0, 0, 0, 50 });
			std::string ammo_num{ std::to_string(ac.bullets) };
			ammo_num = ammo_title + ammo_num;
			std::string health_num{ std::to_string(health.health_points) };
			health_num = health_title + health_num;

			engine::FontManager::Load(ammo_num.c_str(), engine::BLACK, 24, "resources/fonts/retro_gaming.ttf");
			engine::FontManager::Draw(ammo_num.c_str(), V2_int{ 50, 90 }, V2_int{100, 32});
			engine::FontManager::Unload(ammo_num.c_str());

			engine::FontManager::Load(health_num.c_str(), engine::BLACK, 24, "resources/fonts/retro_gaming.ttf");
			engine::FontManager::Draw(health_num.c_str(), V2_int{ 50, 50 }, V2_int{ 100, 32 });
			engine::FontManager::Unload(health_num.c_str());
		}
	}
};
