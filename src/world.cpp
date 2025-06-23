#include "world.h"
#include "gravitation.h"
#include "spring.h"
#include "collision.h"

World::~World()
{

}

void World::Initialize(Vector2 gravity, size_t poolSize)
{
    World::gravity = gravity;
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{
    Body* body = new Body(position, size, color);
    m_bodies.push_back(body);
    return body;
}

Body* World::CreateBody(const Body::Type& type, const Vector2& position,float mass, float size, const Color& color)
{
    Body* body = new Body(type, position, mass, size, color);
    m_bodies.push_back(body);
    return body;
}

Spring* World::CreateSpring(Body* selectedBody, Body* connectedBody, float restLength, float stiffness)
{
    Spring* spring = new Spring(selectedBody, connectedBody, restLength, stiffness);
    m_springs.push_back(spring);
    return spring;
}

void World::Step(float timeStep)
{
    if (!simulate) return;

    if (gravitation > 0 ) ApplyGravitation(m_bodies, gravitation);

    //apply spring forces
    for (auto spring : m_springs)
    {
        spring->ApplyForce(0.8f, springStiffMultiply);
    }
    
    for (auto body : m_bodies)
    {
        body->Step(timeStep);
        body->ClearForce();
    }

    if (!m_contacts.empty()) m_contacts.clear();
    Collision::CreateContacts(m_bodies, m_contacts);
    Collision::SeparateContacts(m_contacts);
    Collision::ResolveContacts(m_contacts);
}

void World::Draw(const Scene& scene)
{
    for (auto spring : m_springs)
    {
        spring->Draw(scene);
    }

    for (auto body : m_bodies)
    {
        body->Draw(scene);

    }
}

void World::DestroyAll()
{
    if (!m_bodies.empty())
    {
        for (auto body : m_bodies)
        {
            delete body;
        }
        m_bodies.clear();
    }

    if (!m_springs.empty())
    {
        for (auto spring : m_springs)
        {
            delete spring;
        }
        m_springs.clear();
    }
    
}
