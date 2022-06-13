#pragma once

#include "engine_device.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "../game/gameObject.hpp"

#include <memory>
#include <vector>

namespace scandium{
	
	class Application{

		public:
			static const int WIDTH = 800;
			static const int HEIGHT = 600;
			
			Application();
			~Application();

			Application(const Application &) = delete;
			Application &operator=(const Application &) = delete;

			void run();
			
		private:
			void loadGameObjects();

			Window renderWindow{WIDTH, HEIGHT, "Bruh"};
			EngineDevice engineDevice{renderWindow};
			Renderer renderer{renderWindow, engineDevice};
			std::vector<GameObject> gameObjects;
	};
}