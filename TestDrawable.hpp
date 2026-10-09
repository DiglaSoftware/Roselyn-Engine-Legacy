#ifndef TEST_DRAWABLE_HPP
#define TEST_DRAWABLE_HPP

#include "RoselynObject.hpp"
#include "Texture.hpp"

namespace RoselynEngine {
	class TestDrawable : public RoselynObject {
		public:
			TestDrawable();
			void Draw() override;
			void SetTexture(Texture &texture);

		private:
			Texture* Texture = nullptr;
			unsigned int VBO, VAO, EBO;
	};
}

#endif