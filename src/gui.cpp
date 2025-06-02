#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "body.h"
#include "gui.h"

#define GUI_DATA(data) TextFormat("%0.2f", data), &data

void GUI::Initialize()
{
	GuiLoadStyle("../raygui/styles/jungle/style_jungle.rgs");
}

void GUI::Update()
{
    mouseOverGui = physicsWindowActive && CheckCollisionPointRec(GetMousePosition(), Rectangle{ windowAnchor.x + 0, windowAnchor.y + 0, 270, 450 });
    
	if (IsKeyPressed(KEY_TAB)) physicsWindowActive = !physicsWindowActive;
}

void GUI::Draw()
{
	if (editDropdownMode) GuiLock();

	if (physicsWindowActive)
	{
		physicsWindowActive = !GuiWindowBox(Rectangle{ windowAnchor.x + 0, windowAnchor.y + 0, 312, 472 }, "Physics");

		GuiToggle(Rectangle{ windowAnchor.x + 24, windowAnchor.y + 432, 120, 24 }, "Simulate", &World::simulate);
		resetPressed = GuiButton(Rectangle{ windowAnchor.x + 168, windowAnchor.y + 432, 120, 24 }, "Reset");

		//Body
		GuiGroupBox(Rectangle{ bodyAnchor.x + 0, bodyAnchor.y + 0, 264, 176 }, "Body");
		GuiSliderBar(Rectangle{ bodyAnchor.x + 104, bodyAnchor.y + 16, 120, 16 }, "Mass", GUI_DATA(bodyMass), 0, 100);
		GuiSliderBar(Rectangle{ bodyAnchor.x + 104, bodyAnchor.y + 40, 120, 16 }, "Size", GUI_DATA(bodySize), 0, 100);
		GuiSliderBar(Rectangle{ bodyAnchor.x + 104, bodyAnchor.y + 64, 120, 16 }, "Gravity Scale", GUI_DATA(bodyGravityScale), -50, 50);
		GuiSliderBar(Rectangle{ bodyAnchor.x + 104, bodyAnchor.y + 88, 120, 16 }, "Damping", GUI_DATA(bodyDamping), 0, 1);
		GuiSliderBar(Rectangle{ bodyAnchor.x + 104, bodyAnchor.y + 112, 120, 16 }, "Restitution", GUI_DATA(bodyRestitution), 0, 1);
		GuiLabel(Rectangle{ bodyAnchor.x + 32, bodyAnchor.y + 136, 120, 24 }, "Body Type");

		//Spring
		GuiGroupBox(Rectangle{ springAnchor.x + 0, springAnchor.y + 0, 264, 72 }, "Spring");
		GuiSliderBar(Rectangle{ springAnchor.x + 104, springAnchor.y + 16, 120, 16 }, "Damping", GUI_DATA(springDampingValue), 0, 1);
		GuiSliderBar(Rectangle{ springAnchor.x + 104, springAnchor.y + 40, 120, 16 }, "Stiffness",GUI_DATA(springStiffnessValue), 0, 10);
		
		//World
		GuiGroupBox(Rectangle{ worldAnchor.x + 0, worldAnchor.y + -8, 264, 96 }, "World");
		GuiSliderBar(Rectangle{ springAnchor.x + 104, springAnchor.y + 104, 120, 16 }, "Gravitation", GUI_DATA(worldGravitation), -50, 50);
		GuiSlider(Rectangle{ worldAnchor.x + 104, worldAnchor.y + 56, 120, 16 }, "Gravity", GUI_DATA(worldGravity), -50, 50);
		GuiSliderBar(Rectangle{ springAnchor.x + 104, springAnchor.y + 128, 120, 16 }, "Sp Multiplier", GUI_DATA(springMultiValue), 0, 10);
		
		if (GuiDropdownBox(Rectangle{ bodyAnchor.x + 104, bodyAnchor.y + 136, 120, 24 }, "Dynamic;Kinematic;Static", &bodyTypeOptions, editDropdownMode)) editDropdownMode = !editDropdownMode;

	}
	GuiUnlock();
}


Body* GUI::GetBodyIntersect(const Vector2& position, const bodies_t& bodies, const SceneCamera& camera)
{
	for (auto& body : bodies)
	{
		if (CheckCollisionPointCircle(position, body->position, body->size)) return body;
	}
    return nullptr;
}
