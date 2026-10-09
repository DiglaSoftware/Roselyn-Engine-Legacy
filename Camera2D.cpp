#include "Camera2D.hpp"
#include <glm/glm.hpp>

namespace RoselynEngine {
	Camera2D::Camera2D(float Left, float Right, float Bottom, float Top, float Near, float Far) {
		this->ProjectionMatrix = glm::ortho(Left, Right, Bottom, Top, Near, Far);
	}

	void Camera2D::Draw() { }

	glm::mat4 Camera2D::GetProjectionMatrix() {
		return this->ProjectionMatrix;
	}

	glm::mat4 Camera2D::GetViewMatrix() {
		this->ViewMatrix = this->Transform.GetMatrix();
		return this->ViewMatrix;
	}

	glm::mat4 Camera2D::GetViewProjectionMatrix() {
		this->ViewMatrix = this->Transform.GetMatrix();
		return this->ProjectionMatrix * this->ViewMatrix;
	}
}