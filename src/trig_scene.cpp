#include "trig_scene.h"

float DegToRad(float degrees) 
{
	return degrees / (PI * 180);
}

float RadToDeg(float radians) 
{
	return radians * (180 / PI);
}

float Vector2Length(const Vector2& v)
{
	return sqrtf((v.x * v.x) + (v.y * v.y));
}

Vector2 Vector2Normalize(const Vector2& v)
{
	float l = Vector2Length(v);
	if (l != 0)
	{
		return Vector2{ v.x / l, v.y / l };
	}
	return Vector2{ 0 };
}

void TrigScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void TrigScene::Update()
{
}

void TrigScene::Draw()
{
	m_camera->BeginMode();


	DrawGrid(10, 5, WHITE);
	//DrawCircleV(m_camera->WorldToScreen(Vector2{ 0,0 }), m_camera->WorldToScreen(1), RED);
	//DrawCircle(Vector2{ 0,0 }, 1, RED);
	float radius = 3.0f;
	float rate = 0.8f;
	float time = (float) GetTime() * rate;


	int steps = 50;
	for (int i = 0; i < steps; i++)
	{
		float theta = ((float) i / steps) * (2.0f * PI); //0-1
		float x = cosf(theta) * radius * 0.5f;
		float y = sinf(theta) * radius;
		DrawCircle(Vector2{ x,y }, 0.25, RED);
	}

	//sin / cos
	for (float x = -10.0f; x < 10.0f; x += 0.2f)
	{
		float theta = time + (x / 20) * (2.0f * PI); //0-1
		float c = cosf(theta) * radius;
		float s = sinf(theta) * radius;
		DrawCircle(Vector2{ x,c }, 0.25, PURPLE);
		DrawCircle(Vector2{ x,s }, 0.25, BLUE);

	}

	float theta = time;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;
	DrawCircle(Vector2{ x,y }, 0.25, YELLOW);

	float angle = atan2(y, x); //angle to object from our position
	

	m_camera->EndMode();
}

void TrigScene::DrawGUI()
{
}
