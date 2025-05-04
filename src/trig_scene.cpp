#include "trig_scene.h"

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

	DrawCircle(0, 0, 200, RED);

	m_camera->EndMode();
}

void TrigScene::DrawGUI()
{
}
