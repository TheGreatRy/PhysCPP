#pragma once
#include "raymath.h"

struct AABB
{
	Vector2 center;
	Vector2 size;

	AABB() = default;
	AABB(const Vector2& center, const Vector2& size) : 
		center{ center },
		size{size}
	{}

	Vector2 extents() const { return Vector2Divide(size, Vector2{ 2,2 });}
	Vector2 min() const { return center - extents(); }
	Vector2 max() const { return center + extents(); }
};