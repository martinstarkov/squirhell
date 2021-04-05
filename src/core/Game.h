#pragma once

#include <engine/Include.h>

class Game : public engine::Engine {
public:
	void Init() {
		std::cout << "Hi" << std::endl;
	}
	void Update() {
		std::cout << "Update" << std::endl;
	}
	void Render() {
		std::cout << "Render" << std::endl;
	}
};