#pragma once

struct AmmoPackComponent {
	AmmoPackComponent() = default;
	AmmoPackComponent(int ammo) : ammo{ ammo } {}
	int ammo{ 0 }; // amount of ammo in the pack.
};