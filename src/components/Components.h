#pragma once

#include <protegon.h>
#include <unordered_map>
#include <cassert>

using namespace engine;

struct PlayerInputComponent {
	PlayerInputComponent() = default;
};

struct SpriteKeyComponent {
	SpriteKeyComponent() = default;
	SpriteKeyComponent(const char* key, const V2_int& sprite_size) : 
		key{ key },
		sprite_size{ sprite_size } {}
	const char* key{ nullptr };
	V2_int sprite_size;
};

struct InventoryComponent2 {
	InventoryComponent2() = default;
	// key:tag component id of entity, value:pair of entity and item count
	std::unordered_map<int, std::pair<ecs::Entity, int>> inventory;

	void Add(ecs::Entity& item) {
		assert(item.HasComponent<TagComponent>() && "Cannot add item without TagComponent id to inventory");
		auto id = item.GetComponent<TagComponent>().id;
		auto it = inventory.find(id);
		// inventory contains item
		if (it != inventory.end()) {
			// TODO: TEMPORARY reconsider assertion
			//assert(entity == item);
			auto& entity = it->second.first;
			auto& count = it->second.second;
			++count;
		} else { //inventory does not contain item
			inventory.emplace(id, std::pair<ecs::Entity, int>(item, 1));
		}
	}

	void Remove(int item_id) {
		auto it = inventory.find(item_id);
		// inventory contains item
		if (it != inventory.end()) {
			auto& entity = it->second.first;
			auto& count = it->second.second;
			if (count > 1) {
				--count;
			} else {
				inventory.erase(it);
			}
		}
	}

	bool Has(int item_id) const {
		auto it = inventory.find(item_id);
		return it != inventory.end() && it->second.second > 0;
	}

	int Amount(int item_id) const {
		auto it = inventory.find(item_id);
		if (it != inventory.end()) {
			return  it->second.second;
		} else {
			return 0;
		}
	}

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

struct HealthPackComponent {
	HealthPackComponent() = default;
	HealthPackComponent(int health) : health{ health } {}
	int health{ 0 }; // amount of health in the pack.
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

struct EnemyBulletComponent {
	EnemyBulletComponent() = default;
	EnemyBulletComponent(int damage) : damage{ damage } {}
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

struct RangedEnemyComponent {
	RangedEnemyComponent() = default;
	RangedEnemyComponent(int damage) : damage{ damage } {}
	int damage{ 0 };
};

struct ItemComponent {
	ItemComponent() = default;
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