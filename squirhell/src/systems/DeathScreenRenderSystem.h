#pragma once

#include <protegon.h>

#include "components/TagComponents.h"
#include "core/Hell.h"

class DeathScreenRenderSystem : public ecs::System<DeathScreenComponent> {
public:
	std::string death_title = "You Died!";
	std::string reset_title = "Try Again";
	V2_int title_size{ 200, 64 };
	void Update() override {
		for (auto [entity, dsc] : entities) {
			auto screen_size = engine::Engine::GetScreenSize();
			auto title_position = screen_size / 2 - title_size/2;
			engine::TextureManager::DrawSolidRectangle({ 0,0 }, engine::Engine::GetScreenSize(), engine::RED);
			engine::FontManager::Load(death_title.c_str(), engine::BLACK, 24, "resources/fonts/retro_gaming.ttf");
			engine::FontManager::Draw(death_title.c_str(), title_position, title_size);
			engine::FontManager::Unload(death_title.c_str());
			V2_int button_size{ 100, 30 };
			auto button_position = screen_size / 2 - button_size / 2;
			button_position.y += 80;
			engine::TextureManager::DrawSolidRectangle(button_position, button_size, engine::SILVER);
			engine::FontManager::Load(reset_title.c_str(), engine::BLACK, 16, "resources/fonts/retro_gaming.ttf");
			engine::FontManager::Draw(reset_title.c_str(), button_position, button_size);
			engine::FontManager::Unload(reset_title.c_str());
			auto mouse = engine::InputHandler::GetMousePosition();
			if (engine::collision::PointvsAABB(mouse, { button_position, button_size }) && engine::InputHandler::MousePressed(MouseButton::LEFT)) {
				GetManager().Clear();
				GetManager().Refresh();
				Hell::Generate(GetManager());
			}
		}
	}
};
