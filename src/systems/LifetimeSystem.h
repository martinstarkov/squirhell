#pragma once

#include <protegon.h>

class LifetimeSystem : public ecs::System<LifetimeComponent> {
public:
	virtual void Update() override final {
		for (auto& [entity, life] : entities) {
			// TODO: In the future, for falling platforms, decrease lifetime if there is a bottom collision
			//CollisionComponent* collision = pair.second->getComponent<CollisionComponent>();
			//if (collision->bottom) { lifetime->isDying = true; }
			if (life.is_dying) {
				if (life.lifetime * Engine::GetFPS() >= 1.0) {
					life.lifetime -= 1.0 / Engine::GetFPS();
				} else {
					life.lifetime = 0.0;
				}
			}
			if (life.lifetime == 0.0) {
				entity.Destroy();
			}
		}
		GetManager().Refresh();
	}
};