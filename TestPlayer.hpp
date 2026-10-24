#pragma once

#include "RoselynObject.hpp"
#include "InputManager.hpp"
#include "LevelManager.hpp"
#include "Time.hpp"

using namespace RoselynEngine;

namespace RoselynGame {
	class TestPlayer : public RoselynObject {
		public:
			TestPlayer() {
				Engine::GetWindow()->HideCursor();
			}

			void Draw() override {}
			void Tick() override {
				if (LevelManager::GetCurrentLevel() != nullptr) {
					if (LevelManager::GetCurrentLevel()->LevelCamera != nullptr) {
						Camera* camera = LevelManager::GetCurrentLevel()->LevelCamera;
						
						Vector2f mouse = InputManager::GetMouseDelta();

						camera->Transform.Rotation.y += mouse.x * 0.1f;
						camera->Transform.Rotation.z += mouse.y * 0.1f;

						if (camera->Transform.Rotation.z > 89.0f) camera->Transform.Rotation.z = 89.0f;
						if (camera->Transform.Rotation.z < -89.0f) camera->Transform.Rotation.z = -89.0f;

						if (InputManager::IsKeyPressed(GLFW_KEY_ESCAPE)) Engine::Quit();

						if (InputManager::IsKeyPressed(GLFW_KEY_SPACE)) camera->Transform.Position.y += 2.5f * Time::GetDeltaTime();
						if (InputManager::IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) camera->Transform.Position.y -= 2.5f * Time::GetDeltaTime();
						if (InputManager::IsKeyPressed(GLFW_KEY_W)) camera->Transform.Position += (camera->Transform.GetForwardVector() * 2.5f * Time::GetDeltaTime());
						if (InputManager::IsKeyPressed(GLFW_KEY_S)) camera->Transform.Position -= (camera->Transform.GetForwardVector() * 2.5f * Time::GetDeltaTime());
						if (InputManager::IsKeyPressed(GLFW_KEY_A)) camera->Transform.Position -= (camera->Transform.GetRightVector() * 2.5f * Time::GetDeltaTime());
						if (InputManager::IsKeyPressed(GLFW_KEY_D)) camera->Transform.Position += (camera->Transform.GetRightVector() * 2.5f * Time::GetDeltaTime());
					}
				}
			}
	};
}