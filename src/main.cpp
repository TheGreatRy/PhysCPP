/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "scene.h"
#include "trig_scene.h"
#include "vector_scene.h"
#include "polar_scene.h"

int main ()
{
	float timeAcumm = 0;
	int windowWidth = 1280;
	int windowHeight = 720;
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(windowWidth, windowHeight, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	
	/*Camera2D camera;
	camera.offset = Vector2{ windowWidth / 2.0f, windowHeight / 2.0f };
	camera.target = Vector2{ 0,0 };
	camera.rotation = 0;
	camera.zoom = 1;*/

	//TrigScene* scene = new TrigScene("Trig", windowWidth, windowHeight);
	VectorScene* scene = new VectorScene("Vector", windowWidth, windowHeight);
	//PolarScene* scene = new PolarScene("Polar", windowWidth, windowHeight);
	scene->Initialize();

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		scene->Update();
		timeAcumm += GetFrameTime();
		while (timeAcumm >= Scene::fixedTimeStep)
		{
			scene->FixedUpdate();
			timeAcumm -= Scene::fixedTimeStep;
		}
		scene->BeginDraw();
		scene->Draw();
		scene->EndDraw();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
