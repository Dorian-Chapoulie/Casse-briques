#pragma once
struct Vector2i {
	Vector2i(float x, float y);
	float x, y;

	Vector2i operator+=(const Vector2i& other);
};
