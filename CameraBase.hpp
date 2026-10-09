#ifndef CAMERA_BASE_HPP
#define CAMERA_BASE_HPP

#include "RoselynObject.hpp"

namespace RoselynEngine {
	class CameraBase : public RoselynObject {
		public:
			virtual glm::mat4 GetProjectionMatrix() = 0;
			virtual glm::mat4 GetViewMatrix() = 0;
			virtual glm::mat4 GetViewProjectionMatrix() = 0;
	};
}

#endif /* CAMERA_BASE_HPP */