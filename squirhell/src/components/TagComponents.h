#pragma once

#include<protegon.h>

struct PlayerInputComponent {
	PlayerInputComponent() = default;
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
	engine::Timer timer;
	int next = 0;
};