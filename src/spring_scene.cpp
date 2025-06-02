#include "spring_scene.h"
#include "math_utils.h"
#include "raymath.h"
#include "raygui.h"
#include "gravitation.h"
#include "gui.h"
#include "spring.h"


void SpringScene::Initialize()
{

	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
	GUI::Initialize();

#pragma region Enemies


	/*Body* body = new Body(Vector2{ 3,0 }, Vector2{ 0 }, 0.25, WHITE);
	m_head = body;
	m_player = m_head;

	for (int i = 0; i < 10; i++)
	{
		Body* newBody = new Body(Vector2{ randf() * 5.0f, randf() * 5.0f }, Vector2{0}, 0.25, RED);
		body->next = newBody;
		body = newBody;
	}*/
#pragma endregion

	Vector2 windowAnchor = { 96, 48 };
}

void SpringScene::Update()
{
	GUI::Update();
	float dt = GetFrameTime();

	if (GUI::simulateActive) World::simulate = !World::simulate;
	if (GUI::resetPressed) m_world->DestroyAll();


	if (!GUI::mouseOverGui)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT))
		{
			//change value to take in menu options
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			float theta = randomf(0, 360);

			body->type = Body::Type{ GUI::bodyTypeOptions };


			body->mass = GUI::bodyMass;
			body->gravityScale = GUI::bodyGravityScale;
			body->damping = GUI::bodyDamping;
			body->size = GUI::bodySize;

			body->ApplyForce(randomOnUnitCircle() * 20, Body::ForceMode::Velocity);
		}
	}

	if (m_selectedBody)
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL))
		{
			if (m_selectedBody->type == Body::Type::Dynamic)
			{
				Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
				Spring::ApplyForce(position, *m_selectedBody, 0, 1);
			}
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
		{
			Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
			m_selectedBody = GUI::GetBodyIntersect(position, m_world->GetBodies(), *m_camera);
		}
	}
		
	m_world->gravity.y = GUI::worldGravity;



	//apply collision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -1;
		}
		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -1;
		}
		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x *= -1;
		}

	}


}

void SpringScene::FixedUpdate()
{
	//apply forces
	m_world->Step(Scene::fixedTimeStep);

	ApplyGravitation(m_world->GetBodies(), GUI::worldGravitation);
}

void SpringScene::Draw()
{
	m_camera->BeginMode();

	//Grid!
	DrawGrid(10, 5, DARKGRAY);

	m_world->Draw(*this);
	if (m_selectedBody) DrawCircleLine(m_selectedBody->position, m_selectedBody->size, YELLOW, 5);

	m_camera->EndMode();
}

void SpringScene::DrawGUI()
{
	GUI::Draw();
}
