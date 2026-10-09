#ifndef CAMERA_3D_HPP
#define CAMERA_3D_HPP

#include "CameraBase.hpp"
#include <glm/glm.hpp>

namespace RoselynEngine {
	class Camera3D : public CameraBase {
		public:
			Camera3D(float fov, float aspect, float near, float far);

			void Draw() override;

			void ProcessInput(float deltaTime);
			void ProcessMouse(float xoffset, float yoffset);

			void RebuildProjectionMatrix(float fov, float aspect, float near, float far) {
				this->ProjectionMatrix = glm::perspective(fov, aspect, near, far);
			}

			glm::mat4 GetProjectionMatrix() override;
			glm::mat4 GetViewMatrix() override;
			glm::mat4 GetViewProjectionMatrix() override;

			glm::vec3 GetFront() {
				return this->Front;
			}

			glm::vec3 GetRight() {
				return this->Right;
			}

			glm::vec3 GetUp() {
				return this->Up;
			}

		private:
			void UpdateCameraVectors();

			glm::mat4 ProjectionMatrix;
			glm::mat4 ViewMatrix;

			float Yaw = -90.0f;
			float Pitch = 0.0f;
			float MovementSpeed = 2.5f;
			float Sensitivity = 0.1f;

			glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 Right;
			glm::vec3 WorldUp = Up;
	};
}

#endif /* CAMERA_3D_HPP */