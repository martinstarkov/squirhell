#pragma once

struct SpriteKeyComponent {
	SpriteKeyComponent() = default;
	SpriteKeyComponent(const char* key) : key{ key } {}
	const char* key{ nullptr };
};