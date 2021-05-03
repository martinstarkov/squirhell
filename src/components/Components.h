#pragma once

#include <protegon.h>

using namespace engine;

struct SpriteKeyComponent {
	SpriteKeyComponent() = default;
	SpriteKeyComponent(const char* key, const V2_int& sprite_size) : 
		key{ key },
		sprite_size{ sprite_size } {}
	const char* key{ nullptr };
	V2_int sprite_size;
};

using CollisionFunction = void(*)(ecs::Entity& target, const engine::Manifold& manifold);

struct HitboxComponent {
	HitboxComponent() = default;
	HitboxComponent(const V2_int& offset) : offset{ offset } {}
	V2_int offset;
	std::vector<ecs::Entity> colliders;
	std::vector<int> ignored_tag_types;
	CollisionFunction function{ nullptr };
};

struct HealthComponent {
	HealthComponent() = default;
	HealthComponent(int max_health) : max_health{ max_health }, health_points{ max_health } {}
	int health_points{ 0 }; // number of health points.
	int max_health{ 0 }; // max health.
};

struct AmmoPackComponent {
	AmmoPackComponent() = default;
	AmmoPackComponent(int ammo) : ammo{ ammo } {}
	int ammo{ 0 }; // amount of ammo in the pack.
};

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

struct AIMovementComponent {
	AIMovementComponent() = default;
	AIMovementComponent(int speed) : speed{ speed } {}
	int speed{ 0 }; // speed of enemy.
};

struct PlayerInputComponent {
	PlayerInputComponent() = default;
};

struct RangeComponent {
	RangeComponent() = default;
	RangeComponent(int range) : range{ range } {}
	int range{ 0 };
};

struct PlacementComponent {
	PlacementComponent() = default;
	V2_int position;
	V2_int size;
	engine::Color color{ engine::colors::GREEN };
};

struct BulletComponent {
	BulletComponent() = default;
	BulletComponent(int damage) : damage{ damage } {}
	int damage{ 0 };
};

struct ShootableComponent {
	ShootableComponent() = default;
};

struct EnemyComponent {
	EnemyComponent() = default;
	EnemyComponent(int damage) : damage{ damage } {}
	int damage{ 0 };
};

struct PickUpComponent {
	PickUpComponent() = default;
};

struct DeathScreenComponent {
	DeathScreenComponent() = default;
};

struct WaveTimerComponent {
	WaveTimerComponent() {
		timer.Start();
	}
	Timer timer;
	int next = 0;
};