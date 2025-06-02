#pragma once
#include <raylib.h>
#include "world.h"

class GUI
{
public:
	static void Update();
	static void Draw();
	static void Initialize();

	static Body* GetBodyIntersect(const Vector2& position, const bodies_t& bodies, const SceneCamera& camera);
public:
	inline static Vector2 windowAnchor = { 72, 48 };
	inline static Vector2 bodyAnchor = { 96, 88 };
	inline static Vector2 springAnchor = { 96, 280 };
	inline static Vector2 worldAnchor = { 96, 376 };

	inline static bool mouseOverGui{ false };
	
	//body values
	inline static bool physicsWindowActive = true;
	inline static bool editDropdownMode = false;
	inline static int bodyTypeOptions = 0;
	inline static float bodyGravityScale = 1.0f;
	inline static float bodyMass = 1.0f;
	inline static float bodySize = 0.2f;
	inline static float bodyDamping = 0.5f;
	inline static float bodyRestitution = 0.0f;
	
	//world values
	inline static float worldGravity{ -9.81f };
	inline static float worldGravitation{ -9.81f };
	inline static float springMultiValue{ 1.0f };
	inline static float springStiffnessValue{ 0.0f };
	inline static float springDampingValue = 0.0f;

	//buttons
	inline static bool simulateActive = true;
	inline static bool resetPressed = false;
};