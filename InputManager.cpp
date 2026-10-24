#include "InputManager.hpp"

namespace RoselynEngine {
	GLFWwindow* InputManager::Window = nullptr;
	std::unordered_map<int, bool> InputManager::KeyStates = {};
	std::unordered_map<int, bool> InputManager::MouseButtonStates = {};
	glm::vec2 InputManager::LastMousePosition = glm::vec2(0.0f);
	glm::vec2 InputManager::MouseDelta = glm::vec2(0.0f);
	glm::vec2 InputManager::ScrollDelta = glm::vec2(0.0f);

	void InputManager::Init(GLFWwindow* window) {
		Window = window;
		glfwSetKeyCallback(Window, key_callback);
		glfwSetMouseButtonCallback(Window, mouse_button_callback);
		glfwSetCursorPosCallback(Window, cursor_position_callback);
		glfwSetScrollCallback(Window, scroll_callback);
	}

	bool InputManager::IsKeyPressed(int key) {
		if (KeyStates.contains(key)) return KeyStates[key];
		return false;
	}

	bool InputManager::IsMouseButtonPressed(int key) {
		if (MouseButtonStates.contains(key)) return MouseButtonStates[key];
		return false;
	}

	Vector2f InputManager::GetMousePosition() {
		return { LastMousePosition.x, LastMousePosition.y };
	}

	Vector2f InputManager::GetMouseDelta() {
		Vector2f temp{ MouseDelta.x, MouseDelta.y };
		MouseDelta.x = 0.0f;
		MouseDelta.y = 0.0f;
		return temp;
	}

	Vector2f InputManager::GetScrollDelta() {
		Vector2f temp{ ScrollDelta.x, ScrollDelta.y };
		ScrollDelta.x = 0.0f;
		ScrollDelta.y = 0.0f;
		return temp;
	}

	void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			KeyStates[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			KeyStates[key] = false;
		}
	}

	void InputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			MouseButtonStates[button] = true;
		}
		else if (action == GLFW_RELEASE) {
			MouseButtonStates[button] = false;
		}
	}

	void InputManager::cursor_position_callback(GLFWwindow* window, double xposIn, double yposIn) {
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (FirstMouse) {
			LastMousePosition.x = xpos;
			LastMousePosition.y = ypos;
			MouseDelta.x = 0.0f;
			MouseDelta.y = 0.0f;
			FirstMouse = false;
			return;
		}

		MouseDelta.x = xpos - LastMousePosition.x;
		MouseDelta.y = LastMousePosition.y - ypos;

		LastMousePosition.x = xpos;
		LastMousePosition.y = ypos;
	}

	void InputManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		ScrollDelta.x = static_cast<float>(xoffset);
		ScrollDelta.y = static_cast<float>(yoffset);
	}
}