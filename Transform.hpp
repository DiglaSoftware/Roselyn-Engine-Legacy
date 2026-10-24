#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.hpp"

namespace RoselynEngine {
	struct Transform3D {
		Vector3f Position { 0.0f, 0.0f, 0.0f };
		Vector3f Rotation { 0.0f, 0.0f, 0.0f };
		Vector3f Scale { 1.0f, 1.0f, 1.0f };

		glm::mat4 GetMatrix() {
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(Position.x, Position.y, Position.z));
			glm::mat4 rotation = glm::mat4(1.0f);
			rotation = glm::rotate(rotation, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			rotation = glm::rotate(rotation, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			rotation = glm::rotate(rotation, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(Scale.x, Scale.y, Scale.z));
			return translation * rotation * scale;
		}

		glm::vec3 GetVec3Position() {
			return glm::vec3(Position.x, Position.y, Position.z);
		}

		glm::vec3 GetVec3Rotation() {
			return glm::vec3(Rotation.x, Rotation.y, Rotation.z);
		}

		glm::vec3 GetVec3Scale() {
			return glm::vec3(Scale.x, Scale.y, Scale.z);
		}

		void AddPosition(const Vector3f& delta) {
			Position.x += delta.x;
			Position.y += delta.y;
			Position.z += delta.z;
		}

		void AddPositionGLM(const glm::vec3& delta) {
			Position.x += delta.x;
			Position.y += delta.y;
			Position.z += delta.z;
		}

		Vector3f GetForwardVector() {
			glm::vec3 Forward;
			Forward.x = cos(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.z));
			Forward.y = sin(glm::radians(Rotation.z));
			Forward.z = sin(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.z));
			Forward = glm::normalize(Forward);

			return { Forward.x, Forward.y, Forward.z };
		}

		Vector3f GetRightVector() {
			glm::vec3 Forward;
			Forward.x = cos(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.z));
			Forward.y = sin(glm::radians(Rotation.z));
			Forward.z = sin(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.z));
			Forward = glm::normalize(Forward);

			glm::vec3 Right = glm::normalize(glm::cross(Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
			
			return { Right.x, Right.y, Right.z };
		}

		Vector3f GetUpVector() {
			glm::vec3 Forward;
			Forward.x = cos(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.z));
			Forward.y = sin(glm::radians(Rotation.z));
			Forward.z = sin(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.z));
			Forward = glm::normalize(Forward);

			glm::vec3 Right = glm::normalize(glm::cross(Forward, glm::vec3(0.0f, 1.0f, 0.0f)));

			glm::vec3 Up = glm::normalize(glm::cross(Right, Forward));

			return { Up.x, Up.y, Up.z };
		}
	};

	struct Transform2D {
		Vector2f Position{ 0.0f, 0.0f };
		float Angle = 0.0f;
		Vector2f Scale{ 1.0f, 1.0f };

		glm::mat4 GetMatrix() {
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(Position.x, Position.y, 0.0f));
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Angle, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(Scale.x, Scale.y, 1.0f));
			return translation * rotation * scale;
		}
	};
}

#endif /* TRANSFORM_HPP */