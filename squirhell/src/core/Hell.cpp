#include "Hell.h"

#include "components/TagComponents.h"
#include "components/SpriteKeyComponent.h"

#include "systems/GameSystems.h"

#include "factories/CreatePlayer.h"
#include "factories/CreateBullet.h"
#include "factories/CreateAcorn.h"
#include "factories/CreateEnemy.h"
#include "factories/CreateAmmoPack.h"

V2_double Hell::GetScale() {
	return { 4, 4 };
}

void Hell::Generate(ecs::Manager& manager) {
	CreatePlayer(manager, { 16, 16 });
	manager.Refresh();
}

void Hell::Create() {
	Generate(manager);
}

void Hell::Update() {
	auto players = manager.GetEntitiesWith<PlayerInputComponent>();
	if (players.size() > 0) {
		auto& player = players.at(0);
		if (player.HasComponent<WaveTimerComponent>()) {
			auto& timer = player.GetComponent<WaveTimerComponent>();
			if (timer.timer.ElapsedSeconds() >= timer.next) {
				engine::RNG<int> rng{ 5,20 };
				auto barrels = rng();
				for (auto i = 0; i < barrels; ++i) {
					CreateEnemy(manager, V2_double::Random(0, engine::Engine::GetScreenWidth(), 0, engine::Engine::GetScreenHeight()));
				}

				CreateAmmoPack(manager, V2_double::Random(0, engine::Engine::GetScreenWidth(), 0, engine::Engine::GetScreenHeight()), 10);
				manager.Refresh();
				timer.timer.Start();
				engine::RNG<int> wave{ 5,15 };
				timer.next = wave();
			}
		}
		manager.UpdateSystem<FiringSystem>();
		manager.UpdateSystem<MovementSystem>();
		manager.UpdateSystem<AIMovementSystem>();
		manager.UpdateSystem<RigidBodySystem>();
		manager.UpdateSystem<HitboxCollisionSystem>();
		manager.UpdateSystem<ShootableSystem>();
		manager.UpdateSystem<PickUpSystem>();
		manager.UpdateSystem<DamageSystem>();
		manager.UpdateSystem<LifetimeSystem>();
		manager.UpdateSystem<HealthSystem>();
	}
}

void Hell::Render() {
	manager.UpdateSystem<BulletRenderSystem>();
	manager.UpdateSystem<SpriteRenderSystem>();
	manager.UpdateSystem<StatDisplaySystem>();
	manager.UpdateSystem<DeathScreenRenderSystem>();
}