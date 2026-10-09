#include "Camera3D.hpp"
#include <glm/glm.hpp>
#include "InputManager.hpp"
#include <iostream>

namespace RoselynEngine {
	Camera3D::Camera3D(float fov, float aspect, float near, float far) {
		this->ProjectionMatrix = glm::perspective(fov, aspect, near, far);
		UpdateCameraVectors();
	}

	void Camera3D::Draw() {}

	glm::mat4 Camera3D::GetProjectionMatrix() {
		return this->ProjectionMatrix;
	}

	glm::mat4 Camera3D::GetViewMatrix() {
		return glm::lookAt(this->Transform.GetVec3Position(), this->Transform.GetVec3Position() + Front, Up);
	}

	glm::mat4 Camera3D::GetViewProjectionMatrix() {
		//return this->ProjectionMatrix * glm::lookAt(Position, Position + Front, Up);
		return this->ProjectionMatrix * glm::lookAt(this->Transform.GetVec3Position(), this->Transform.GetVec3Position() + Front, Up);
	}

	void Camera3D::ProcessMouse(float xoffset, float yoffset) {
		xoffset *= Sensitivity;
		yoffset *= Sensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (Pitch > 89.999f) Pitch = 89.999f;
		if (Pitch < -89.999f) Pitch = -89.999f;

		UpdateCameraVectors();
	}

	void Camera3D::UpdateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));
		//Up = glm::normalize(glm::cross(Right, Front));
	}
}