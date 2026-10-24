#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Utils.hpp"

namespace RoselynEngine {
	struct PointLight {
		Vector3f Position;
		Vector3f Color;
		float Intensity;
	};
}

#endif /* LIGHT_HPP */