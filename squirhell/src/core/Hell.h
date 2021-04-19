#pragma once

#include <protegon.h>

class Hell : public engine::BaseWorld {
public:
	static void Generate(ecs::Manager& manager);
	static V2_double GetScale();
	void Create();
	virtual void Update();
	virtual void Render();
	virtual void Reset() {}
	virtual void Clear() {}
	virtual void SetPlayer(const ecs::Entity& new_player) { p23456 = new_player; }
	virtual ecs::Entity& GetPlayer() { return p23456; }
	virtual ecs::Manager& GetManager() { return manager; }
private:
	ecs::Entity p23456;
	ecs::Manager manager;
};