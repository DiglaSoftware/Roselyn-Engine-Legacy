#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "RoselynObject.hpp"
#include <glm/glm.hpp>

namespace RoselynEngine {
	class Camera : public RoselynObject {
		public:
			Camera();
			~Camera();

			void Draw() override;
			void Tick() override;

			void Make2D(float Left, float Right, float Bottom, float Top, float Near, float Far);
			void Make3D(float fov, float aspect, float near, float far);

			glm::mat4 GetProjectionMatrix();
			glm::mat4 GetViewMatrix();
			glm::mat4 GetViewProjectionMatrix();

		private:
			glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
			glm::mat4 ViewMatrix = glm::mat4(1.0f);
	};
}

#endif /* CAMERA_HPP */