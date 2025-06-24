#include "game_scene.h"
#include "math_utils.h"
#include "raymath.h"
#include "raygui.h"
#include "gravitation.h"
#include "gui.h"
#include "spring.h"


void GameScene::Initialize()
{

	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
	
	GUI::Initialize();
	World::simulate = true;

	count = 3;
	m_spawner = m_world->CreateBody(Body::Type::Static, Vector2{ 0,0 }, 5, Vector2{0.3,0.3}, ColorFromHSV(randomf(360), 1, 1));
	

	Vector2 windowAnchor = { 96, 48 };
}

void GameScene::Update()
{
	if (World::gameOver) return;
	
	GUI::Update();
	float dt = GetFrameTime();

	m_spawner->position = m_camera->ScreenToWorld(GetMousePosition());

	for (auto body : m_world->GetBodies())
	{
		if (GUI::GetBodyIntersect(m_spawner->position, m_world->GetBodies(), *m_camera))
		{
			body->velocity = Vector2Negate(body->velocity * body->restitution);
		}
	}
	

	//apply world gravity	
	m_world->gravity.y = GUI::worldGravity;

	//apply collision
	for (auto body : m_world->GetBodies())
	{
		if (body != m_spawner)
		{
			if (body->position.y < -5 || body->position.x < -9 || body->position.x > 9)
			{
				World::simulate = false;
				World::gameOver = true;
			}
		}

	}

	//if (GUI::resetPressed) m_world->DestroyAll();

	for (auto body : m_world->GetBodies())
	{
		AABB aabb = body->GetAABB();
		AABB worldAABB = m_camera->GetAABB();

		if ((aabb.min().y) < worldAABB.min().y)
		{
			float overlap = (worldAABB.min().y - aabb.min().y); // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if ((aabb.max().y) > worldAABB.max().y)
		{
			float overlap = (worldAABB.max().y - aabb.max().y);  // calculate how far the body has penetrated beyond the world boundary
			body->position.y += 2 * overlap; // move the body back inside the world bounds
			body->velocity.y *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}

		if ((aabb.min().x) < worldAABB.min().x)
		{
			float overlap = (worldAABB.min().x - aabb.min().x); // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
		else if (aabb.max().x > worldAABB.max().x)
		{
			float overlap = (worldAABB.max().x - aabb.max().x);  // calculate how far the body has penetrated beyond the world boundary
			body->position.x += 2 * overlap; // move the body back inside the world bounds
			body->velocity.x *= -body->restitution; // multiple by -restituion to scale and flip velocity
		}
	}
}

void GameScene::FixedUpdate()
{
	if (World::gameOver) return;
	ApplyGravitation(m_world->GetBodies(), GUI::worldGravitation);

	//apply forces
	m_world->Step(Scene::fixedTimeStep);

	count -= Scene::fixedTimeStep;
	if (count <= 0)
	{
		score += 10;
		Body* body = m_world->CreateBody(Body::Type::Dynamic, Vector2{ randomf(-5,5), randomf(0,9) }, GUI::bodyMass, GUI::bodySize, ColorFromHSV(randomf(360), 1, 1));
		body->ApplyForce(randomOnUnitCircle() * 20, Body::ForceMode::Velocity);
		count = 3;
	}
	
}

void GameScene::Draw()
{
	m_camera->BeginMode();

	m_world->Draw(*this);

	DrawText("Score: " + std::to_string(score), Vector2{ -8, 4.5f }, 40, GREEN);

	if (!World::gameOver) DrawText("Keep the balls away from the bottom!", Vector2{ -4.0f, 4.5f }, 40, WHITE);
	else DrawText("YOU LOSE", Vector2{ -2.5f,0 }, 100, RED);

	m_camera->EndMode();
}

void GameScene::DrawGUI()
{
	//GUI::Draw();
}
