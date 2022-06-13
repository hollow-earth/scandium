#include "window.hpp"
#include "application.hpp"

#include <iostream>
#include <stdexcept>

namespace scandium{
	Window::Window(int w, int h, std::string name): width{w}, height{h}, windowName{name} {
		initWindow();
	}

	Window::~Window(){
		glfwDestroyWindow(window);
		glfwTerminate();
		std::cout << "Window destroyed";
	}

	void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS){
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void Window::initWindow(){
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizecallback);
	}

	void Window::framebufferResizecallback(GLFWwindow *window, int width, int height){
		auto rendererWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		rendererWindow->framebufferResized = true;
		rendererWindow->width = width;
		rendererWindow->height = height;
	}
}