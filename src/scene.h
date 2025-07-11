#pragma once
#include "raylib.h"
#include "scene_camera.h"
#include "body.h"
#include <string>

class World;

class Scene
{
	friend struct Body;
	friend struct Spring;
public:

	Scene(const std::string& title, int width, int height, const Color& background = BLACK);
	Scene() {}
	virtual ~Scene();

	virtual void Initialize() = 0;
	virtual void Update() = 0;

	virtual void BeginDraw();
	virtual void EndDraw();
	virtual void FixedUpdate() = 0;
	virtual void Draw() = 0;
	virtual void DrawGUI() = 0;

	bool IsQuit() { return WindowShouldClose(); }

	void SetCamera(SceneCamera* camera) { m_camera = camera; }
	SceneCamera* GetCamera() { return m_camera; }

	static constexpr float fixedTimeStep{ 1.0f / 60.0f };
protected:
	void DrawGrid(float slices, float thickness, const Color& color) const;
	void DrawText(const std::string& text, const Vector2& world, int fontSize, const Color& color) const;
	void DrawCircle(const Vector2& world, float radius, const Color& color) const;
	void DrawRectangle(const Vector2& world, const Vector2& size, const Color& color) const;
	void DrawCircleLines(const Vector2& world, float radius, const Color& color, int pixels = 0) const;
	void DrawLine(const Vector2& v1, const Vector2& v2, float thickness, const Color& color) const;

protected:
	int m_width{ 0 };
	int m_height{ 0 };
	Color m_background{ WHITE };

	SceneCamera* m_camera{ nullptr };
	World* m_world{ nullptr };
};
