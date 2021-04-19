#pragma once

#include <protegon.h>

class Hell : public engine::BaseWorld {
public:
	static V2_double GetScale();
	void Create();
	virtual void Update();
	virtual void Render();
	virtual void Reset() {}
	virtual void Clear() {}
	virtual void SetPlayer(const ecs::Entity& new_player) { player = new_player; }
	virtual ecs::Entity& GetPlayer() { return player; }
	virtual ecs::Manager& GetManager() { return manager; }
private:
	ecs::Entity player;
	ecs::Manager manager;
};