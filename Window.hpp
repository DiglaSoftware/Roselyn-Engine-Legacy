#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>
#include "Utils.hpp"

namespace RoselynEngine {
	class Window {
		public:
			Window(const uint32_t& width, const uint32_t& height, const std::string& title, const bool& resizeable);
			~Window();

			void SetSize(Vector2i& size);
			void SetTitle(std::string& title);

			void Clear();
			void Clear(unsigned char r, unsigned char g, unsigned char b);
			void PollEvents();
			void SwapBuffers();

			void HideCursor();
			void ShowCursor();

			void Close();
			bool IsShoudClose();

			float GetAspect();

			GLFWwindow* GetNative();

		private:
			GLFWwindow* Handle = nullptr;
			uint32_t Width = 800;
			uint32_t Height = 600;
			std::string Title = "Game";
	};
}

#endif /* WINDOW_HPP */