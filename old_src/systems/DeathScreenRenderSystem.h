#pragma once

#include <protegon.h>

#include "components/Components.h"
#include "core/Hell.h"

using namespace engine;

inline bool PointvsRectangle(const V2_double& point, const V2_int& position, const V2_int& size) {
	return (point.x >= position.x &&
			point.y >= position.y &&
			point.x < position.x + size.x &&
			point.y < position.y + size.y);
}

class DeathScreenRenderSystem : public ecs::System<DeathScreenComponent> {
public:
	engine::Text death{
		"You died",
		colors::BLACK,
		"retro_gaming_24",
		{}, { 200, 64 } 
	};
	engine::Text reset{
		"Try Again",
		colors::BLACK,
		"retro_gaming_16",
		{}, { 100, 30 }
	};
	void Update() override {
		auto display_size{ Engine::GetDisplay().first.GetSize() };
		death.SetPosition(display_size / 2 - death.GetArea() / 2);
		reset.SetPosition({ 
			display_size.x / 2 - reset.GetArea().x / 2,
			display_size.y / 2 - reset.GetArea().y / 2 + 80
		});
		for (auto [entity, dsc] : entities) {
			Renderer::DrawSolidRectangle(
				{ 0, 0 }, 
				display_size, 
				colors::RED
			);
			Renderer::DrawText(death);
			V2_int button_size{ 100, 30 };
			Renderer::DrawSolidRectangle(reset.GetPosition(), reset.GetArea(), colors::SILVER);
			auto mouse{ engine::InputHandler::GetMousePosition() };
			Renderer::DrawText(reset);
			if (
				PointvsRectangle(mouse, reset.GetPosition(), reset.GetArea()) &&
				InputHandler::MousePressed(MouseButton::LEFT)) {
				GetManager().Clear();
				GetManager().Refresh();
				Hell::Generate(GetManager());
			}
		}
	}
};
