#include "world.h"
#include "body.h"

Vector2 World::m_gravity{ 0.0f, -9.81f };

World::~World()
{

}

void World::Initialize(Vector2 gravity, size_t poolSize)
{
    World::m_gravity = gravity;
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{
    Body* body = new Body(position, size, color);
    m_bodies.push_back(body);
    return body;
}

void World::Step(float timeStep)
{
    for (auto body : m_bodies)
    {
        body->Step(timeStep);
        body->ClearForce();
    }
}

void World::Draw(const Scene& scene)
{
    for (auto body : m_bodies)
    {
        body->Draw(scene);

    }
}

void World::DestroyAll()
{
    for (auto body : m_bodies)
    {
        delete body;
    }
}
