#include "vector_scene.h"
#include "body.h"
#include "math_utils.h"
#include "raymath.h"
#include "raygui.h"

#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void VectorScene::Initialize()
{

	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();

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

void VectorScene::Update()
{
	float dt = GetFrameTime();

#pragma region PlayerInput

	/*Vector2 input{ 0 };

	if (IsKeyDown(KEY_A)) input.x = -1;
	if (IsKeyDown(KEY_D)) input.x = 1;
	if (IsKeyDown(KEY_S)) input.y = -1;
	if (IsKeyDown(KEY_W)) input.y = 1;
	input = Vector2Normalize(input);
	m_player->velocity = input * 3;

	Body* body = m_head;
	while (body)
	{
		if (body == m_player)
		{

			body->Step(dt);
			body = body->next;
			continue;
		}

		Vector2 direction = m_player->position - body->position;
		direction = Vector2Normalize(direction);

		body->velocity = direction;
		body->Step(dt);
		body = body->next;
	}*/
#pragma endregion

	if (IsMouseButtonPressed(0) && !mouseOverGui)
	{

		//change value to take in menu options
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());
		for (int i = 0; i < 100; i++)
		{
			Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(360), 1, 1));
			float theta = randomf(0, 360);

			body->type = Body::Type{ bodyTypeOptions };
			//standard fireworks
			float x = cosf(theta);
			float y = sin(theta);

			//spread fireworks
			/*float x = cosf(theta) + position.x;
			float y = sinf(theta) + position.y;*/

			//linear line fireworks
			/*float x = position.x;
			float y = position.y;*/
			body->velocity = Vector2{ x, y } *randomf(1, 6);
			body->mass = bodyMass;
			body->gravityScale = bodyGravity;
			body->damping = bodyDamping;

			m_world->m_gravity.y = worldGravity;
		}
	}

	if (IsKeyPressed(KEY_TAB))
	{
		physicsWindowActive = true;
	}

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

void VectorScene::FixedUpdate()
{
	//apply forces
	m_world->Step(Scene::fixedTimeStep);

}

void VectorScene::Draw()
{
	m_camera->BeginMode();

	//Grid!
	DrawGrid(10, 5, DARKGRAY);

	/*Body* body = m_head;
	while (body)
	{

		body->Draw(*this);
		body = body->next;
	}*/
	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	mouseOverGui = physicsWindowActive && CheckCollisionPointRec(GetMousePosition(), Rectangle{ windowAnchor.x + 0, windowAnchor.y + 0, 270, 385 });
	// raygui: controls drawing
	//----------------------------------------------------------------------------------
	if (editDropdownMode) GuiLock();

	if (physicsWindowActive)
	{
		physicsWindowActive = !GuiWindowBox(Rectangle{ windowAnchor.x + 0, windowAnchor.y + 0, 270, 385 }, "Physics");
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 40, 120, 16 }, "BODY GRAVITY", GUI_DATA(bodyGravity), -50, 50);
		if (GuiTextBox(Rectangle{ windowAnchor.x + 32, windowAnchor.y + 168, 72, 24 }, bodyTypeText, 128, bodyTypeTextEditMode)) bodyTypeTextEditMode = !bodyTypeTextEditMode;
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 72, 120, 16 }, "BODY MASS", GUI_DATA(bodyMass), 1, 500);
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 104, 120, 16 }, "BODY SIZE", GUI_DATA(bodySize), 1, 10);
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 136, 120, 16 }, "BODY DAMPING", GUI_DATA(bodyDamping), 0.001f, 10.0f);
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 328, 120, 16 }, "WORLD GRAVITY", GUI_DATA(worldGravity), -50.0f, 50.0f);
		if (GuiDropdownBox(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 168, 120, 24 }, "DYNAMIC; KINEMATIC; STATIC", &bodyTypeOptions, editDropdownMode)) editDropdownMode = !editDropdownMode;
	}

	GuiUnlock();

}
