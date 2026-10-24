#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>
#include <GLFW/glfw3.h>

namespace RoselynEngine {
	class Time {
		public:
			static void Update() {
				//auto now = std::chrono::high_resolution_clock::now();
				//float current = std::chrono::duration<float>(now - Start).count();
				double current = glfwGetTime();
				DeltaTime = current - LastTime;
				LastTime = current;

				if (DeltaTime > 0.1) DeltaTime = 0.1;
			}
			static float GetDeltaTime() { return (float)DeltaTime; }
			static float GetTotalTime() { return (float)LastTime; }

		private:
			inline static std::chrono::time_point<std::chrono::high_resolution_clock> Start = std::chrono::high_resolution_clock::now();
			inline static double LastTime = 0.0;
			inline static double DeltaTime = 0.0;
	};
}

#endif /* TIME_HPP */