#ifndef ROSELYN_OBJECT_HPP
#define ROSELYN_OBJECT_HPP

#include "Transform.hpp"

namespace RoselynEngine {
	class RoselynObject {
		public:
			virtual void Draw() = 0;
			virtual void Tick() = 0;

			Transform3D Transform;
	};
}

#endif /* ROSELYN_OBJECT_HPP */