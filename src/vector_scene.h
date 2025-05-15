#pragma once
#include "scene.h"

class VectorScene : public Scene
{
public:

	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) :
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
	struct Body* m_head{ nullptr };
	struct Body* m_player{ nullptr };

	Vector2 windowAnchor{ 96, 48 };
	bool mouseOverGui{ false };

	bool physicsWindowActive = true;
	bool editDropdownMode = false;
	int bodyTypeOptions = 0;
	bool bodyTypeTextEditMode = false;
	char bodyTypeText[128] = "BODY TYPE";
	float bodyGravity = 1.0f;
	float bodyMass = 1.0f;
	float bodySize = 1.0f;
	float bodyDamping = 0.5f;
	float worldGravity{ -9.81f };
};
