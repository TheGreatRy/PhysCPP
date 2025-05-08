#include "body.h"
#include "raymath.h"

void Body::Step(float scale)
{
	position += velocity * scale;
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}
