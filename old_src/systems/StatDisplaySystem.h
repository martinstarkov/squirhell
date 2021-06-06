#pragma once

#include <protegon.h>

#include "components/Components.h"

using namespace engine;

class StatDisplaySystem : public ecs::System<PlayerInputComponent, AmmoComponent, HealthComponent, InventoryComponent2> {
public:
	engine::Text health_text{
		"Health: ",
		colors::BLACK,
		"retro_gaming_24",
		{ 50, 50 }, { 100, 32 }
	};
	engine::Text ammo_text{
		"Ammo: ",
		colors::BLACK,
		"retro_gaming_24",
		{ 50, 90 }, { 100, 32 }
	};
	engine::Text grass_text{
		"Grass: ",
		colors::BLACK,
		"retro_gaming_24",
		{ 50, 130 }, { 100, 32 }
	};
	void Update() override {
		for (auto [entity, player, ammo, health, inventory] : entities) {

			auto health_percent = 100 * health.health_points / health.max_health;

			auto grass_item = Hasher::HashCString("grass");

			std::string new_grass_text{ "Grass: " + std::to_string(inventory.Amount(grass_item)) };
			grass_text.SetContent(new_grass_text.c_str());

			Renderer::DrawSolidRectangle(
				{ 150, 50 }, 
				{ 100, 32 }, 
				colors::RED
			);
			Renderer::DrawSolidRectangle(
				{ 150, 50 }, 
				{ health_percent, 32 }, 
				colors::GREEN
			);

			std::string new_ammo_text{ "Ammo: " + std::to_string(ammo.bullets) };
			ammo_text.SetContent(new_ammo_text.c_str());
			Renderer::DrawText(ammo_text);
			Renderer::DrawText(health_text);
			Renderer::DrawText(grass_text);
		}
	}
};
