#include "Engine.hpp"
#include "Time.hpp"
#include "LevelManager.hpp"
#include "InputManager.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <thread>

namespace RoselynEngine {
	bool Engine::Inited = false;
	Window* Engine::GameWindow = nullptr;
	ShaderWorker* Engine::UnlitShaderWorker = nullptr;
	ShaderWorker* Engine::LitShaderWorker = nullptr;

	void Engine::Init() {
		if (Engine::Inited) return;
		if (!glfwInit()) {
			std::cerr << "ROSELYN::ENGINE | Failed to initialize GLFW" << std::endl;
			return;
		}
		std::cout << "ROSELYN::WINDOW | GLFW initialized" << std::endl;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, true);

		Engine::GameWindow = new Window(800, 600, "Roselyn Game", true);
		InputManager::Init(Engine::GameWindow->GetNative());
		Engine::UnlitShaderWorker = new ShaderWorker("Engine/unlit.vert", "Engine/unlit.frag");
		//Engine::LitShaderWorker = new ShaderWorker("Engine/lit.vert", "Engine/lit.frag");

		Engine::Inited = true;
	}

	void Engine::Run() {
		if (!Engine::Inited) {
			std::cout << "ROSELYN::ENGINE | Engine is not inited! Call Engine::Init() before Engine::Run()" << std::endl;
			return;
		}

		while (!Engine::GameWindow->IsShoudClose()) {
			Time::Update();
			Engine::GameWindow->Clear(252, 186, 3);

			if (LevelManager::GetCurrentLevel() == nullptr) {
				Engine::GameWindow->SwapBuffers();
				Engine::GameWindow->PollEvents();

				if (Time::GetDeltaTime() < 1.0 / 60.0) {
					double SleepTime = (1.0 / 60.0 - Time::GetDeltaTime()) * 1000.0;
					std::this_thread::sleep_for(std::chrono::milliseconds((int)SleepTime));
				}
				continue;
			}

			for (int i = 0; i < LevelManager::GetCurrentLevel()->Objects.size(); i++) {
				RoselynObject* object = LevelManager::GetCurrentLevel()->Objects[i];
				object->Tick();
			}

			Engine::UnlitShaderWorker->Use();
			if (LevelManager::GetCurrentLevel()->LevelCamera != nullptr) {
				glm::mat4 viewProjection = LevelManager::GetCurrentLevel()->LevelCamera->GetViewProjectionMatrix();
				Engine::UnlitShaderWorker->SetMat4("ViewProjection", viewProjection);
			}

			for (int i = 0; i < LevelManager::GetCurrentLevel()->Objects.size(); i++) {
				RoselynObject* object = LevelManager::GetCurrentLevel()->Objects[i];
				glm::mat4 model = object->Transform.GetMatrix();
				Engine::UnlitShaderWorker->SetMat4("Model", model);
				object->Draw();
			}

			Engine::GameWindow->SwapBuffers();
			Engine::GameWindow->PollEvents();

			if (Time::GetDeltaTime() < 1 / 60) {
				double SleepTime = (1 / 60 - Time::GetDeltaTime()) * 1000.0;
				std::this_thread::sleep_for(std::chrono::milliseconds((int)SleepTime));
			}
		}
	}

	void Engine::Shutdown() {
		Engine::GameWindow->Close();
		delete Engine::GameWindow;
		delete Engine::UnlitShaderWorker;
		//delete Engine::LitShaderWorker;

		glfwTerminate();
		Engine::Inited = false;
	}

	void Engine::Quit() {
		Engine::GameWindow->Close();
	}

	Window* Engine::GetWindow() {
		return Engine::GameWindow;
	}
}