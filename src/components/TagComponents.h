#pragma once

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