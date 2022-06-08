#include "renderer.hpp"
#include "application.hpp"

#include <iostream>
#include <stdexcept>

namespace scandium{
	RendererWindow::RendererWindow(int w, int h, std::string name): width{w}, height{h}, windowName{name} {
		initWindow();
	}

	RendererWindow::~RendererWindow(){
		glfwDestroyWindow(window);
		glfwTerminate();
		std::cout << "Window destroyed";
	}

	void RendererWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS){
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void RendererWindow::initWindow(){
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizecallback);
	}

	void RendererWindow::framebufferResizecallback(GLFWwindow *window, int width, int height){
		auto rendererWindow = reinterpret_cast<RendererWindow*>(glfwGetWindowUserPointer(window));
		rendererWindow->framebufferResized = true;
		rendererWindow->width = width;
		rendererWindow->height = height;
	}
}