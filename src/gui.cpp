#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "body.h"
#include "gui.h"

#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void GUI::Update()
{
    mouseOverGui = physicsWindowActive && CheckCollisionPointRec(GetMousePosition(), Rectangle{ windowAnchor.x + 0, windowAnchor.y + 0, 270, 385 });
    if (IsKeyPressed(KEY_TAB)) physicsWindowActive = !physicsWindowActive;
}

void GUI::Draw()
{
	if (editDropdownMode) GuiLock();

	if (physicsWindowActive)
	{
		physicsWindowActive = !GuiWindowBox(Rectangle{ windowAnchor.x + 0, windowAnchor.y + 0, 270, 385 }, "Physics");
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 40, 120, 16 }, "BODY GRAVITY", GUI_DATA(bodyGravity), -50, 50);
		if (GuiTextBox(Rectangle{ windowAnchor.x + 32, windowAnchor.y + 168, 72, 24 }, bodyTypeText, 128, bodyTypeTextEditMode)) bodyTypeTextEditMode = !bodyTypeTextEditMode;
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 72, 120, 16 }, "BODY MASS", GUI_DATA(bodyMass), 1, 500);
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 104, 120, 16 }, "BODY SIZE", GUI_DATA(bodySize), 0.01f, 10.0f);
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 136, 120, 16 }, "BODY DAMPING", GUI_DATA(bodyDamping), 0.001f, 10.0f);
		GuiSlider(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 328, 120, 16 }, "WORLD GRAVITY", GUI_DATA(worldGravity), -50.0f, 50.0f);
		if (GuiDropdownBox(Rectangle{ windowAnchor.x + 104, windowAnchor.y + 168, 120, 24 }, "DYNAMIC; KINEMATIC; STATIC", &bodyTypeOptions, editDropdownMode)) editDropdownMode = !editDropdownMode;
	}

	GuiUnlock();
}

Body* GUI::GetBodyIntersect(const Vector2& position,const bodies_t& bodies, const SceneCamera& camera)
{
	for (auto& body : bodies)
	{
		if (CheckCollisionPointCircle(position, body->position, body->size)) return body;
	}
    return nullptr;
}
