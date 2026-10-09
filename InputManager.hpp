#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include "Utils.hpp"

namespace RoselynEngine {
	class InputManager {
		public:
			static void Init(GLFWwindow* window);
			static bool IsKeyPressed(int key);
			static bool IsMouseButtonPressed(int button);
			static Vector2f GetMousePosition();
			static Vector2f GetMouseDelta();
			static Vector2f GetScrollDelta();
		private:
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

			static GLFWwindow* Window;
			static std::unordered_map<int, bool> KeyStates;
			static std::unordered_map<int, bool> MouseButtonStates;
			static glm::vec2 LastMousePosition;
			static glm::vec2 MouseDelta;
			static glm::vec2 ScrollDelta;
			inline static bool FirstMouse = true;
	};
}

#endif