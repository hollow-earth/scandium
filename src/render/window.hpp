#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace scandium{
	class Window{
		public:
			Window(int w, int h, std::string name);
			~Window();

			Window(const Window &) = delete;					// what is this???
			Window &operator=(const Window &) = delete;			// no fucking clue what this does
			bool wasWindowResized() {return framebufferResized; }
			void resetWindowResizedFlag() {framebufferResized = false; }

			bool shouldClose() { return glfwWindowShouldClose(window); }
			VkExtent2D getExtent() {return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
			void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

		private:
			static void framebufferResizecallback(GLFWwindow *window, int width, int height);
			int width;
			int height;
			bool framebufferResized = false;
			
			std::string windowName;
			GLFWwindow* window;

			void initWindow();
	};

}