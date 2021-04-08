#include "Hell.h"

#include "components/TagComponents.h"
#include "components/SpriteKeyComponent.h"

#include "systems/GameSystems.h"

#include "factories/CreatePlayer.h"
#include "factories/CreateBullet.h"
#include "factories/CreateAcorn.h"

V2_double Hell::GetScale() {
	return { 4, 4 };
}

void Hell::Create() {
	auto barrels = 1;
	for (auto i = 0; i < barrels; ++i) {
		CreateAcorn(manager, V2_double::Random(0, engine::Engine::GetScreenWidth(), 0, engine::Engine::GetScreenHeight()));
	}
	

	player = CreatePlayer(manager, { 16, 16 });
	manager.Refresh();
}

void Hell::Update() {
	auto [tc, sc, rc, rbc] = player.GetComponents<TransformComponent, SizeComponent, RenderComponent, RigidBodyComponent>();
	manager.UpdateSystem<FiringSystem>();
	manager.UpdateSystem<MovementSystem>();
	manager.UpdateSystem<RigidBodySystem>();
	manager.UpdateSystem<HitboxCollisionSystem>();
	manager.UpdateSystem<ShootableSystem>();
	manager.UpdateSystem<LifetimeSystem>();
	manager.UpdateSystem<HealthSystem>();
}

void Hell::Render() {
	manager.UpdateSystem<BulletRenderSystem>();
	manager.UpdateSystem<SpriteRenderSystem>();
}