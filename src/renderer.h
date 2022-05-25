#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace scandium{
	class rendererWindow{
		public:
			rendererWindow(int w, int h, std::string name);
			~rendererWindow();

			rendererWindow(const rendererWindow &) = delete;					// what is this???
			rendererWindow &operator=(const rendererWindow &) = delete;			// no fucking clue what this does

			bool shouldClose() { return glfwWindowShouldClose(window); }
			void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

		private:
			const int width;
			const int height;
			
			std::string windowName;
			GLFWwindow* window;

			void initWindow();
	};

}