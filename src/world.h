#pragma once
#include <vector>
#include "raylib.h"
#include "scene.h"

typedef std::vector<Body*> bodies_t;
class World
{
public:
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30);
	Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(const Body::Type& type, const Vector2& position,float mass, float size, const Color& color);
	void Step(float timeStep);
	void Draw(const class Scene& scene);
	void DestroyAll();
	bodies_t& GetBodies(){ return m_bodies; }

	inline static Vector2 gravity{ 0.0f, -9.81f };
	inline static float gravitation{ 0 };
	inline static float springStiffMultiply{ 0 };
	inline static bool simulate{ false };

private:
	bodies_t m_bodies;
};