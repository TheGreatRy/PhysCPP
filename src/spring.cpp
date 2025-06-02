#include "spring.h"
#include "raymath.h"
#include "scene.h"

void Spring::ApplyForce(float damping, float kMultiplier)
{
	// Step 1: Calculate direction vector from bodyB to bodyA
	Vector2 direction = bodyA->position - bodyB->position;
	float lengthSquared = Vector2Length(direction);

	// Avoid division by zero or tiny spring length
	if (lengthSquared <= EPSILON) return;

	// Step 2: Calculate spring displacement
	float length = sqrtf(lengthSquared);
	float displacement = length - restLength; // Stretching if > 0, compressed if < 0

	// Step 3: Apply Hooke's Law: F = -k * x
	float forceMagnitude = -(k * kMultiplier) * displacement;

	// Step 4: Normalize direction and calculate spring force vector
	Vector2 normalizedDirection = direction / length;
	Vector2 force = normalizedDirection * forceMagnitude;

	// Step 5: Dampen the spring to reduce oscillation
	Vector2 velocityDifference = bodyA->velocity - bodyB->velocity;
	float dampingAmount = Vector2DotProduct(velocityDifference, normalizedDirection) * damping;
	Vector2 dampingForce = normalizedDirection * dampingAmount;

	// Subtract damping from spring force
	force -= dampingForce;

	// Step 6: Apply equal and opposite forces to the two bodies
	bodyA->ApplyForce(force);
	bodyB->ApplyForce(Vector2Negate(force));
}

void Spring::ApplyForce(const Vector2& position, Body& body, float restLength, float k)
{
	// Step 1: Calculate direction vector from bodyB to bodyA
	Vector2 direction = position - body.position;
	float lengthSquared = Vector2Length(direction);

	// Avoid division by zero or tiny spring length
	if (lengthSquared <= EPSILON) return;

	// Step 2: Calculate spring displacement
	float length = sqrtf(lengthSquared);
	float displacement = length - restLength; // Stretching if > 0, compressed if < 0

	// Step 3: Apply Hooke's Law: F = -k * x
	float forceMagnitude = -k * displacement;

	// Step 4: Normalize direction and calculate spring force vector
	Vector2 normalizedDirection = direction / length;
	Vector2 force = normalizedDirection * forceMagnitude;

	body.ApplyForce(Vector2Negate(force));
}

void Spring::Draw(const Scene& scene)
{
	scene.DrawLine(bodyA->position, bodyB->position, 3, WHITE);
}
