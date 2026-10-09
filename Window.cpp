#include "Window.hpp"
#include <iostream>
#include <glad/glad.h>

namespace RoselynEngine {
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		
	}

	Window::Window(const uint32_t& width, const uint32_t& height, const std::string& title, const bool& resizeable) {
		std::cout << "ROSELYN::WINDOW | Creating window and initializing GLAD" << std::endl;

		if (!glfwInit()) {
			std::cout << "ROSELYN::WINDOW | GLFW failure" << std::endl;
			return;
		}

		std::cout << "ROSELYN::WINDOW | GLFW initialized" << std::endl;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, resizeable);

		this->Handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!this->Handle) {
			std::cout << "ROSELYN::WINDOW | GLFW window failure" << std::endl;
			glfwTerminate();
			return;
		}

		this->Width = width;
		this->Height = height;
		this->Title = title;

		std::cout << "ROSELYN::WINDOW | GLFW window created" << std::endl;

		glfwMakeContextCurrent(this->Handle);
		glfwSetFramebufferSizeCallback(this->Handle, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "ROSELYN::WINDOW | GLAD failure" << std::endl;
			glfwDestroyWindow(this->Handle);
			glfwTerminate();
			return;
		}

		glEnable(GL_DEPTH_TEST);

		std::cout << "ROSELYN::WINDOW | Window creation complete" << std::endl;
	}

	Window::~Window() {
		glfwDestroyWindow(this->Handle);
		glfwTerminate();
	}

	void Window::SetSize(Vector2i& size) {
		glfwSetWindowSize(this->Handle, size.x, size.y);
	}

	void Window::SetTitle(std::string& title) {
		glfwSetWindowTitle(this->Handle, title.c_str());
	}

	void Window::Clear() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Clear(unsigned char r, unsigned char g, unsigned char b) {
		glClearColor((float)r / 256, (float)g / 255, (float)b / 255, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::PollEvents() { glfwPollEvents(); }

	void Window::SwapBuffers() { glfwSwapBuffers(this->Handle); }

	bool Window::IsShoudClose() {
		return glfwWindowShouldClose(this->Handle);
	}

	void Window::Close() {
		glfwSetWindowShouldClose(this->Handle, 1);
	}

	void Window::HideCursor() {
		glfwSetInputMode(this->Handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::ShowCursor() {
		glfwSetInputMode(this->Handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	float Window::GetAspect() {
		int width, height;
		glfwGetWindowSize(this->Handle, &width, &height);
		return (float)width / (float)height;
	}

	GLFWwindow* Window::GetNative() {
		return this->Handle;
	}
}