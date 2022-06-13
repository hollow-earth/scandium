#pragma once

#include "../render/scandium_model.hpp"

#include <glm/glm.hpp>
#include <memory>

namespace scandium
{
	struct Transform2DComponent{
		glm::vec2 translation{};
		glm::vec2 scale{1.0f, 1.0f};
		float rotation;
		glm::mat2 mat2() { 
			const float s = glm::sin(rotation);
			const float c = glm::cos(rotation);
			glm::mat2 rotMatrix{{c, s}, {-s, c}};
			glm::mat2 scaleMat{{scale.x, 0.0f}, {0.0f, scale.y}}; // Takes columns, not rows
			return rotMatrix * scaleMat;
		}
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
			Transform2DComponent transform2d{};
		private:
			GameObject(id_t objId) : id{objId} {}
			id_t id;
	};
}
