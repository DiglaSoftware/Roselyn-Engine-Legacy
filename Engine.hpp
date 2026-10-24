#ifndef ENGINE_HPP
#define ENGINE_Hpp

#include "Window.hpp"
#include "ShaderWorker.hpp"

namespace RoselynEngine {
	class Engine {
		public:
			static void Init();
			static void Run();
			static void Shutdown();
			static void Quit();
			static Window* GetWindow();
		private:
			static bool Inited;
			static Window* GameWindow;
			static ShaderWorker* UnlitShaderWorker;
			static ShaderWorker* LitShaderWorker;
	};
}

#endif /* ENGINE_HPP */