#include "Camera.hpp"

namespace RoselynEngine {
	Camera::Camera() {
	
	}

	Camera::~Camera() {
	
	}

	void Camera::Draw() {}
	void Camera::Tick() {}

	void Camera::Make2D(float Left, float Right, float Bottom, float Top, float Near, float Far) {
		this->ProjectionMatrix = glm::ortho(Left, Right, Bottom, Top, Near, Far);
	}
	
	void Camera::Make3D(float fov, float aspect, float near, float far) {
		this->ProjectionMatrix = glm::perspective(fov, aspect, near, far);
	}

	glm::mat4 Camera::GetProjectionMatrix() {
		return this->ProjectionMatrix;
	}

	glm::mat4 Camera::GetViewMatrix() {
		this->ViewMatrix = glm::lookAt(this->Transform.GetVec3Position(), this->Transform.GetVec3Position() + this->Transform.GetForwardVector().ToGLM(), this->Transform.GetUpVector().ToGLM());
		return this->ViewMatrix;
	}

	glm::mat4 Camera::GetViewProjectionMatrix() {
		this->ViewMatrix = glm::lookAt(this->Transform.GetVec3Position(), this->Transform.GetVec3Position() + this->Transform.GetForwardVector().ToGLM(), this->Transform.GetUpVector().ToGLM());
		return this->ProjectionMatrix * this->ViewMatrix;
	}
}