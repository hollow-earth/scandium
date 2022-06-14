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

		/*! @brief Position vector for the GameObject.
		 *  Keep in mind that Vulkan works with a y-axis pointing downwards.
		 *  The vector is of form {x, y}
		 *  @param[in] x x component of the vector
		 *	@param[in] y y component of the vector, non-standard Cartesian coordinates (pointing downwards)
		*/
		glm::vec2 position = {0.0f, 0.0f};
		
		/*! @brief Performs GameObject rotation about itself.
		 * 	This is only done in the XY plane.
		 *  Keep in mind that Vulkan works with a y-axis pointing downwards.
		 *  @param[in] theta The angle in radians.
		*/
		void rotate(const float theta);

		/*! @brief Performs GameObject scaling.
		 * 	This is only done in the XY plane.
		 *  @param[in] x_scaling The x scale factor, float
		 * 	@param[in] y_scaling The y scale factor, float
		*/
		void scale(float x_scaling, float y_scaling);
		
		/*! @brief Performs GameObject scaling.
		 * 	This is only done in the XY plane.
		 *  @param[in] scaling The scale factor, float. Broadcasted on both the x and y axes.
		*/
		void scale(float scaling);

		/*! @brief Performs GameObject scaling.
		 * 	This is only done in the XY plane. 
		 *  @param[in] scaleMat The scaling matrix of form {{x_scaling, 0.0f},{0.0f, y_scaling}}
		*/
		void scale(glm::mat2x2 scaleMat);

		/*! @brief Performs GameObject translation.
		 * 	This is only done in the XY plane. Keep in mind that Vulkan works with a y-axis pointing downwards.
		 *  @param[in] x_translation float
		 *  @param[in] y_translation float
		*/
		void translate(float x_translation, float y_translation);

		/*! @brief Performs the transform operations.
		 * 	This is only done in the XY plane. Returns rotation * scaling.
		 *  @returns glm::mat2x2 
		*/
		glm::mat2x2 transform();
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
