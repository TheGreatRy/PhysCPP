#pragma once
#include "scene.h"

class GameScene : public Scene
{
public:

	GameScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene{ title, width, height, background }
	{
		//
	}
	// Inherited via Scene
	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;

private:
	Body* m_spawner{ nullptr };
	float count{ 0 };
	int score{ 0 };
};
