#pragma once

#include <protegon.h>

#include "components/AmmoComponent.h"
#include "components/EntitySizeComponent.h"
#include "factories/CreateBullet.h"

class FiringSystem : public ecs::System<AmmoComponent, TransformComponent, EntitySizeComponent> {
public:
	void Update() override {
		for (auto [entity, ammo, tc, sc] : entities) {
			/*if (!ammo.timer.IsRunning()) {
				ammo.timer.Start();
			}*/
			if (engine::InputHandler::KeyPressed(Key::SPACE) &&
				ammo.bullets > 0 &&
				ammo.timer.ElapsedSeconds() > ammo.reload_delay) {

				--ammo.bullets;
				CreateBullet(entity.GetManager(), ammo.lifetime, tc, sc);
				entity.GetManager().Refresh();
				// Testart reload timer.
				ammo.timer.Start();
			}
		}
	}
};
