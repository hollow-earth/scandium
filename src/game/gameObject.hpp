#pragma once

#include "../render/scandium_model.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include <memory>

namespace scandium
{	
	struct Transform2DComponent{
		glm::mat2x2 scaleMatrix = {{1.0f, 0.0f},{0.0f, 1.0f}};
		glm::mat2x2 rotationMatrix = {{1.0f, 0.0f},{0.0f, 1.0f}};
		glm::vec2 position = {0.0f, 0.0f};
		
		void rotate(const float theta);
		void scale(float x_scaling, float y_scaling);
		void translate(float x_translation, float y_translation);
		glm::mat2 transform();
	};

	class GameObject{
		public:
			using id_t = unsigned int;
			
			static GameObject createGameObject(){
				static id_t currentID = 0;
				return GameObject(currentID++);
			}

			GameObject(const GameObject &) = delete;
			GameObject &operator=(const GameObject &) = delete;
			GameObject(GameObject &&) = default;
			GameObject &operator=(GameObject &&) = default;

			id_t getID() { return id; }
			std::shared_ptr<ScandiumModel> model{};
			glm::vec3 color{};
			
			Transform2DComponent Transform2D;
		
		private:
			GameObject(id_t objId) : id{objId} {}
			id_t id;
	};
}
