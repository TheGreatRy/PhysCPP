#include "polar_scene.h"
#include "polar.h"

void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ m_width / 2.0f, m_height / 2.0f });
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{
	m_camera->BeginMode();

	//Grid!
	DrawGrid(10, 5, WHITE);

	float a = 2.0f;
	float b = 1.0f;
	float k = 10.0f;

	int steps = 50;
	for (int i = 0; i < steps; i++)
	{
		float theta = ((float) i / steps) * (2.0f * PI); //0-1

		//Archimedean
		//float radius = a + (b * theta);

		//Cardioid
		//float radius = a * (1 + cosf(theta));
		
		//Limacon
		//float radius = a + b * cosf(theta);

		//Rose
		//float radius = a * cosf(k * theta);

		//User
		float radius = a + cosf(b * theta) / sinf(b*theta);

		Polar polar{ theta, radius };
		DrawCircle(polar, 0.25, GREEN);
		
	}


	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}
