#pragma once

struct AIMovementComponent {
	AIMovementComponent() = default;
	AIMovementComponent(int speed) : speed{ speed } {}
	int speed{ 0 }; // speed of enemy.
};