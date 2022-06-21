#include "application.hpp"
#include "render_system.hpp"
#include "camera.hpp"

#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <stdexcept>

namespace scandium {

	Application::Application(){
		loadGameObjects();
	}

	Application::~Application(){}

	void Application::run(){
		RenderSystem renderSystem{engineDevice, renderer.getSwapChainRenderPass()};
		Camera mainCamera{};

		while(!renderWindow.shouldClose()){
			glfwPollEvents();
			float aspect = renderer.getAspectRation();
			//mainCamera.setOrthographicProjection(-aspect, aspect, -1, 1,-1, 1); // For 2D
			mainCamera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.0f, 10.0f); // For 3D
			if (auto commandBuffer = renderer.beginFrame()){
				renderer.beginSwapChainRenderPass(commandBuffer);
				renderSystem.renderGameObjects(commandBuffer, gameObjects, mainCamera);
				renderer.endSwapChainRenderPass(commandBuffer);
				renderer.endFrame();
			}
		}
		vkDeviceWaitIdle(engineDevice.device());
	}

	std::unique_ptr<ScandiumModel> createCubeModel(EngineDevice& device, glm::vec3 offset) {
	std::vector<ScandiumModel::Vertex> vertices{
		// left face (white)
		{{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
		{{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
		{{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
		{{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
		{{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},
		{{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
	
		// right face (yellow)
		{{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
		{{.5f, .5f, .5f}, {.8f, .8f, .1f}},
		{{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
		{{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
		{{.5f, .5f, -.5f}, {.8f, .8f, .1f}},
		{{.5f, .5f, .5f}, {.8f, .8f, .1f}},
	
		// top face (orange, remember y axis points down)
		{{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
		{{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
		{{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
		{{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
		{{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
		{{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
	
		// bottom face (red)
		{{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
		{{.5f, .5f, .5f}, {.8f, .1f, .1f}},
		{{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
		{{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
		{{.5f, .5f, -.5f}, {.8f, .1f, .1f}},
		{{.5f, .5f, .5f}, {.8f, .1f, .1f}},
	
		// nose face (blue)
		{{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
		{{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
		{{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
		{{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
		{{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
		{{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
	
		// tail face (green)
		{{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
		{{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
		{{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
		{{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
		{{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
		{{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
	
	};
	for (auto& v : vertices) {
		v.position += offset;
	}
	return std::make_unique<ScandiumModel>(device, vertices);
	}

	void Application::loadGameObjects(){
		std::shared_ptr<ScandiumModel> scandiumModel = createCubeModel(engineDevice, {.0f, .0f, .0f});
		auto cube = GameObject::createGameObject();	
		cube.model = scandiumModel;
		cube.Transform2D.translate(0.0f, 0.0f, 0.5f);
		cube.Transform2D.scale(0.5f, 0.5f, 0.5f);
		gameObjects.push_back(std::move(cube));
	}
}