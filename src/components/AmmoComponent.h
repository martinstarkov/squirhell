#pragma once

#include <protegon.h>

struct AmmoComponent {
	AmmoComponent() = default;
	AmmoComponent(int bullets, double reload_delay = 0.1, double lifetime = 1) : bullets{ bullets }, reload_delay{ reload_delay }, lifetime{ lifetime } {
		timer.Start();
	}
	double lifetime{ 1 }; // lifetime of bullet on screen (seconds).
	int bullets{ 0 }; // number of ammunition.
	double reload_delay{ 0.1 }; // seconds.
	engine::Timer timer;
};