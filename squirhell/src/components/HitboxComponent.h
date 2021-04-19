#pragma once

#include <protegon.h>

enum class HitboxType {
	NONE,
	CIRCLE,
	RECTANGLE
};

struct HitboxShape {
	virtual double GetRadius() { return 0; }
	virtual V2_int GetSize() { return {}; }
	virtual HitboxType GetType() { return HitboxType::NONE; }
};

struct CircleHitbox : public HitboxShape {
	virtual double GetRadius() override final { return radius; }
	virtual HitboxType GetType() override final { return HitboxType::CIRCLE; }
	CircleHitbox() = delete;
	CircleHitbox(double radius) : radius{ radius } {}
	double radius;
};

struct RectangleHitbox : public HitboxShape {
	virtual V2_int GetSize() override final { return size; }
	virtual HitboxType GetType() override final { return HitboxType::RECTANGLE; }
	RectangleHitbox() = delete;
	RectangleHitbox(const V2_int& size) : size{ size } {}
	V2_int size;
};

struct HitboxComponent {
	HitboxComponent() = default;
	HitboxComponent(HitboxShape * shape) : shape{ shape } {}
	HitboxComponent(HitboxShape* shape, V2_int offset) : shape{ shape }, offset{ offset } {}
	~HitboxComponent() { 
		delete shape; 
		shape = nullptr; 
	}
	V2_int offset;
	HitboxShape* shape{ nullptr };
	std::vector<ecs::Entity> colliders;
};