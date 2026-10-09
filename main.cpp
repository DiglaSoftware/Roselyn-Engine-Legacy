#include "Window.hpp"
#include "InputManager.hpp"
#include "ShaderWorker.hpp"
#include "Texture.hpp"
#include "TestDrawable.hpp"
#include "Camera2D.hpp"
#include "Camera3D.hpp"
#include "Time.hpp"
#include "StaticMesh.hpp"
#include "Mesh.hpp"
#include <thread>

#include <iostream>

using namespace RoselynEngine;

int main() {
	Window window(800, 600, "Roselyn Game", true);
	InputManager::Init(window.GetNative());
	ShaderWorker shaderWorker("default.vert", "default.frag", true);

	Texture TEX_Floor;
	Texture TEX_Puddle;
	Texture TEX_Cup;

	TEX_Floor.LoadFromFile("Tiles.png");
	TEX_Puddle.LoadFromFile("Tea.png");

	Mesh MESH_Floor("floor.obj");
	Mesh MESH_Puddle("puddle.obj");
	Mesh MESH_Cup("cup.obj");

	StaticMesh SM_Floor;
	SM_Floor.SetTexture(TEX_Floor);
	SM_Floor.SetMesh(MESH_Floor);

	StaticMesh SM_Puddle;
	SM_Puddle.SetTexture(TEX_Puddle);
	SM_Puddle.SetMesh(MESH_Puddle);

	StaticMesh SM_Cup;
	SM_Cup.SetTexture(TEX_Cup);
	SM_Cup.SetMesh(MESH_Cup);

	Camera3D camera(60.0f, window.GetAspect(), 0.01f, 100.0f);
	window.HideCursor();

	float MovementSpeed = 3.0f;

	while (!window.IsShoudClose()) {
		Time::Update();
		window.Clear(252, 186, 3);

		Vector2f mouse = InputManager::GetMouseDelta();

		if (InputManager::IsKeyPressed(GLFW_KEY_ESCAPE)) window.Close();
		camera.ProcessMouse(mouse.x, mouse.y);

		camera.RebuildProjectionMatrix(90.0f, window.GetAspect(), 0.01f, 1000000.0f);

		if (InputManager::IsKeyPressed(GLFW_KEY_W)) camera.Transform.AddPositionGLM(camera.GetFront() * MovementSpeed * Time::GetDeltaTime());
		if (InputManager::IsKeyPressed(GLFW_KEY_S)) camera.Transform.AddPositionGLM(-camera.GetFront() * MovementSpeed * Time::GetDeltaTime());
		if (InputManager::IsKeyPressed(GLFW_KEY_A)) camera.Transform.AddPositionGLM(-camera.GetRight() * MovementSpeed * Time::GetDeltaTime());
		if (InputManager::IsKeyPressed(GLFW_KEY_D)) camera.Transform.AddPositionGLM(camera.GetRight() * MovementSpeed * Time::GetDeltaTime());
		if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) camera.Transform.AddPositionGLM(-camera.GetUp() * MovementSpeed * Time::GetDeltaTime());
		if (InputManager::IsKeyPressed(GLFW_KEY_SPACE)) camera.Transform.AddPositionGLM(camera.GetUp() * MovementSpeed * Time::GetDeltaTime());

		if (InputManager::IsKeyPressed(GLFW_KEY_R)) {
			camera.Transform.Position = { 0.0f, 0.0f, 0.0f };
		}

		MovementSpeed += InputManager::GetScrollDelta().y * 0.5f;
		if (MovementSpeed < 0.1f) MovementSpeed = 0.1f;

		shaderWorker.Use();
		glm::mat4 viewProjection = camera.GetViewProjectionMatrix();
		shaderWorker.SetMat4("ViewProjection", viewProjection);

		glm::mat4 model = SM_Floor.Transform.GetMatrix();
		shaderWorker.SetMat4("Model", model);
		SM_Floor.Draw();

		model = SM_Puddle.Transform.GetMatrix();
		shaderWorker.SetMat4("Model", model);
		SM_Puddle.Draw();

		model = SM_Cup.Transform.GetMatrix();
		shaderWorker.SetMat4("Model", model);
		SM_Cup.Draw();

		std::cout << camera.Transform.Position.z << std::endl;

		window.SwapBuffers();
		window.PollEvents();

		if (Time::GetDeltaTime() < 1 / 60) {
			double SleepTime = (1 / 60 - Time::GetDeltaTime()) * 1000.0;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)SleepTime));
		}
	}

	return 0;
}