#pragma once

#include <Protegon.h>

struct AIMovementSystem {
	void operator()(ecs::Entity entity) {
		ptgn::PrintLine("Entity manager address: ", &entity.GetManager());
	}
}