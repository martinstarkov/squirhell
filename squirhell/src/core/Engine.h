#pragma once

#include <protegon.h>

class Squirhell : public protegon::Engine {
public:
	void Init() {
		std::cout << "Init" << std::endl;
	}
	void Update() {
		std::cout << "Update" << std::endl;
	}
	void Render() {
		std::cout << "Render" << std::endl;
	}
};