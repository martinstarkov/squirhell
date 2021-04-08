#pragma once

struct HealthComponent {
	HealthComponent() = default;
	HealthComponent(int health_points) : health_points{ health_points } {}
	int health_points{ 0 }; // number of health points.
};