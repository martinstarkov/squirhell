#pragma once

#include <protegon.h>

struct EntitySizeComponent {
	EntitySizeComponent() = default;
	EntitySizeComponent(V2_int size, V2_double scale = { 1, 1 }) : size{ size }, scale{ scale } {}

	V2_int size;
	V2_double scale{ 1, 1 };
};