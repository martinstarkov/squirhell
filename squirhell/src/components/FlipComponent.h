#pragma once
#include <protegon.h>

struct FlipComponent {
	FlipComponent() = default;
	Flip direction_x{Flip::NONE};
	Flip direction_y{Flip::NONE};
};