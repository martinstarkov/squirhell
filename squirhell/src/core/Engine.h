#pragma once

#include <protegon.h>
#include "Hell.h"

class Squirhell : public engine::Engine {
public:
	Hell hell;
	void Init() {
		hell.Create();
	}
	void Update() {
		hell.Update();
	}
	void Render() {
		hell.Render();
	}
};