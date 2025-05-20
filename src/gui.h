#pragma once
#include <raylib.h>
#include "world.h"

class GUI
{
public:
	static void Update();
	static void Draw();

	static struct Body* GetBodyIntersect(const Vector2& position, const bodies_t& bodies, const SceneCamera& camera);
public:
	inline static Vector2 windowAnchor{ 96, 48 };
	inline static bool mouseOverGui{ false };
	
	inline static bool physicsWindowActive = true;
	inline static bool editDropdownMode = false;
	inline static int bodyTypeOptions = 0;
	inline static bool bodyTypeTextEditMode = false;
	inline static char bodyTypeText[128] = "BODY TYPE";
	inline static float bodyGravity = 1.0f;
	inline static float bodyMass = 1.0f;
	inline static float bodySize = 0.2f;
	inline static float bodyDamping = 0.5f;
	inline static float worldGravity{ -9.81f };
};