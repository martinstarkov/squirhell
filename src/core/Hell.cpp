#include "Hell.h"

#include "components/Components.h"
#include "systems/GameSystems.h"
#include "factories/Factories.h"

using namespace engine;

V2_double Hell::GetScale() {
	return { 4, 4 };
}

void Hell::Generate(ecs::Manager& manager) {
	CreatePlayer(manager);
	CreateWall(manager, V2_int{160,160});
	CreateGrass(manager, V2_int{320,160});
	manager.Refresh();
}

void Hell::Create() {
	TextureManager::Load("player", "resources/player.png");
	TextureManager::Load("acorn", "resources/acorn.png");
	TextureManager::Load("enemy", "resources/enemy.png");
	TextureManager::Load("ammopack", "resources/ammopack.png");
	TextureManager::Load("healthpack", "resources/healthpack.png");
	TextureManager::Load("hell_wall", "resources/hellwall.png");
	TextureManager::Load("grass", "resources/grass.png");
	FontManager::Load("retro_gaming_24", "resources/fonts/retro_gaming.ttf", 24);
	FontManager::Load("retro_gaming_16", "resources/fonts/retro_gaming.ttf", 16);
	manager.AddSystem<FiringSystem>();
	manager.AddSystem<MovementSystem>();
	manager.AddSystem<AIMovementSystem>();
	manager.AddSystem<SpriteRenderSystem>();
	manager.AddSystem<HitboxCollisionSystem>();
	manager.AddSystem<ShootableSystem>();
	manager.AddSystem<DamageSystem>();
	manager.AddSystem<PickUpSystem>();
	manager.AddSystem<HealthSystem>();
	manager.AddSystem<RigidBodySystem>();
	manager.AddSystem<BulletRenderSystem>();
	manager.AddSystem<LifetimeSystem>();
	manager.AddSystem<StatDisplaySystem>();
	manager.AddSystem<DeathScreenRenderSystem>();
	manager.AddSystem<PlacementSystem>();
	manager.AddSystem<PlacementRenderSystem>();
	Generate(manager);
}

void Hell::Update() {
	auto players = manager.GetEntitiesWith<PlayerInputComponent>();
	auto display_size{ Engine::GetDisplay().first.GetSize() };
	if (players.size() > 0) {
		auto& player = players.at(0);
		if (player.HasComponent<WaveTimerComponent>()) {
			auto& timer = player.GetComponent<WaveTimerComponent>();
			if (timer.timer.ElapsedSeconds() >= timer.next) {
				engine::RNG<int> rng{ 3,8 };
				auto enemies = rng();
				for (auto i = 0; i < enemies; ++i) {
					CreateEnemy(manager, V2_double::Random(
						0, 
						display_size.x, 
						0, 
						display_size.y
					));
				}
		
				CreateAmmoPack(manager, 
							   V2_double::Random(
								   0, 
								   display_size.x, 
								   0, 
								   display_size.y
							   ), 
							   10
				);
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
		manager.UpdateSystem<PlacementSystem>();
	}
}

void Hell::Render() {
	manager.UpdateSystem<BulletRenderSystem>();
	manager.UpdateSystem<SpriteRenderSystem>();
	manager.UpdateSystem<StatDisplaySystem>();
	manager.UpdateSystem<PlacementRenderSystem>();
	manager.UpdateSystem<DeathScreenRenderSystem>();
}