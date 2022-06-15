#pragma once

#include "../render/scandium_model.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace scandium
{	
	struct Transform2DComponent{
		glm::vec3 position = {0.0f, 0.0f, 0.0f};
		glm::vec3 scaling = {1.0f, 1.0f, 1.0f};
		glm::vec3 rotation = {0.0f, 0.0f, 1.0f};

		void rotate(const float theta_x, const float theta_y, const float theta_z);
		void rotate(const float theta_z);
		void flip_x();
		void flip_y();
		void scale(float x_scaling, float y_scaling);
		void scale(float scaling);
		//void scale(glm::mat2x2 scaleMat);
		void translate(float x_translation, float y_translation);
		glm::mat4x4 transform();
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
			
			//TODO find a way to store color
			Transform2DComponent Transform2D;
		
		private:
			GameObject(id_t objId) : id{objId} {}
			id_t id;
	};
}
