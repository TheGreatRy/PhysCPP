#include "body.h"
#include "world.h"
#include "integrator.h"
#include "raymath.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;

	force += (World::gravity * gravityScale) * mass;
	acceleration = (force * invMass);
	
	SemiImplicitIntegration(*this, dt);
}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force, ForceMode forceMode)
{
	switch (forceMode)
	{
	case Body::ForceMode::Force:
		this->force += force;
		break;
	case Body::ForceMode::Impluse:
		this->velocity += force * invMass;
		break;
	case Body::ForceMode::Velocity:
		this->velocity += force;
		break;
	default:
		break;

	}
}
