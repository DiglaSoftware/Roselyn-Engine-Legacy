#ifndef CAMERA_2D_HPP
#define CAMERA_2D_HPP

#include "CameraBase.hpp"
#include <glm/glm.hpp>

namespace RoselynEngine {
	class Camera2D : public CameraBase {
		public:
			Camera2D(float Left, float Right, float Bottom, float Top, float Near, float Far);

			void Draw() override;

			glm::mat4 GetProjectionMatrix() override;
			glm::mat4 GetViewMatrix() override;
			glm::mat4 GetViewProjectionMatrix() override;

		private:
			glm::mat4 ProjectionMatrix;
			glm::mat4 ViewMatrix;
	};
}

#endif /* CAMERA_2D_HPP */