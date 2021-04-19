#pragma once

struct HealthComponent {
	HealthComponent() = default;
	HealthComponent(int max_health) : max_health{ max_health }, health_points { max_health } {}
	int health_points{ 0 }; // number of health points.
	int max_health{ 0 }; // max health.
};