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

			auto health_percent = 100 * health.health_points / health.max_health;

			engine::FontManager::Load(health_title.c_str(), engine::BLACK, 24, "resources/fonts/retro_gaming.ttf");
			engine::FontManager::Draw(health_title.c_str(), V2_int{ 50, 50 }, V2_int{ 100, 32 });
			engine::FontManager::Unload(health_title.c_str());


			engine::TextureManager::DrawSolidRectangle(V2_int{ 150,50 }, V2_int{ 100, 32 }, engine::RED);
			engine::TextureManager::DrawSolidRectangle(V2_int{ 150,50 }, V2_int{ health_percent, 32 }, engine::GREEN);

			std::string ammo_num{ std::to_string(ac.bullets) };
			ammo_num = ammo_title + ammo_num;
			engine::FontManager::Load(ammo_num.c_str(), engine::BLACK, 24, "resources/fonts/retro_gaming.ttf");
			engine::FontManager::Draw(ammo_num.c_str(), V2_int{ 50, 90 }, V2_int{100, 32});
			engine::FontManager::Unload(ammo_num.c_str());
		}
	}
};
