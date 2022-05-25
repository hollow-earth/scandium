#include "renderer.h"
#include "application.h"
#include <iostream>

namespace scandium{
	rendererWindow::rendererWindow(int w, int h, std::string name): width{w}, height{h}, windowName{name} {
		initWindow();
	}

	rendererWindow::~rendererWindow(){
		glfwDestroyWindow(window);
		glfwTerminate();
		std::cout << "Window destroyed";
	}

	void rendererWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS){
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void rendererWindow::initWindow(){
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}
}