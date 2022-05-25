#pragma once

#include "renderer.h"
#include "pipeline.h"

namespace scandium{
	
	class Application{

		public:
			static const int WIDTH = 800;
			static const int HEIGHT = 600;
			void run();
			
		private:
			rendererWindow renderWindow{WIDTH, HEIGHT, "Bruh"};
			ScandiumPipeline scandiumPipeline{"./shaders/simple_shader.vert.spv", "./shaders/simple_shader.frag.spv"};
	};
}