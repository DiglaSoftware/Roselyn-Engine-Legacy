#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "RoselynObject.hpp"
#include "Camera.hpp"
#include <vector>
#include <string>

namespace RoselynEngine {
	struct Level {
		std::string Name = "New level";
		std::vector<RoselynObject*> Objects;
		Camera* LevelCamera = nullptr;

		Vector3f AmbientLightColor = { 0.1f, 0.1f, 0.1f };
		float AmbientLightIntensity = 1.0f;
	};

	//class Level {
	//	public:
	//		std::string GetName() const { return LevelName; }
	//		Camera* GetCamera() const { return &LevelCamera; }
	//		std::vector<RoselynObject*> Objects;
	//	private:
	//		std::string LevelName = "New level";
	//		Camera LevelCamera;
	//};
}

#endif /* LEVEL_HPP */