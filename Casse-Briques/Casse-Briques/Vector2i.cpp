#include "Vector2i.h"

Vector2i::Vector2i(float x, float y) : x(x), y(y) {}
Vector2i Vector2i::operator+=(const Vector2i& other) {
	return Vector2i(x + other.x, y + other.y);
}