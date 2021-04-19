#pragma once

#include <protegon.h>

#include "components/Components.h"

static void CreateDeathScreen(ecs::Manager& manager) {
	manager.Clear();
	auto death_screen = manager.CreateEntity();
	death_screen.AddComponent<DeathScreenComponent>();
};