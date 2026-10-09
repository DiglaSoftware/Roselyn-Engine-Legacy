#ifndef ENGINE_HPP
#define ENGINE_Hpp

#include "Window.hpp"

namespace RoselynEngine {
	class Engine {
		public:
			void Init();
			void Shutdown();
			void Run();
			void LoadLevel();
		private:
			Window* window;
	};
}

#endif /* ENGINE_HPP */