#include "gameObject.hpp"
#include <iostream>

namespace scandium {
	void Transform2DComponent::scale(float x_scaling, float y_scaling){
		scaling = {x_scaling, y_scaling, 1.0f};
	}

	void Transform2DComponent::scale(float scaling_factor){
		scaling = {scaling_factor, scaling_factor, 1.0f};
	}

	void Transform2DComponent::translate(float x_translation, float y_translation){
		position = {position.x + x_translation, position.y + y_translation, 1.0f};
	}

	void Transform2DComponent::rotate(const float theta_x, 
		const float theta_y, const float theta_z){ rotation = {theta_x, theta_y, theta_z}; }

	void Transform2DComponent::rotate(const float theta_z){ rotation.z = theta_z; }

	// Flip about the x-axis
	void Transform2DComponent::flip_x(){
		rotation.x += glm::pi<float>();
		if (rotation.x >= glm::two_pi<float>()){
			rotation.x -= glm::two_pi<float>();
		}
	}
	
	// Flip about the y-axis
	void Transform2DComponent::flip_y(){
		rotation.y += glm::pi<float>();
		if (rotation.y >= glm::two_pi<float>()){
			rotation.y -= glm::two_pi<float>();
		}
	}

	glm::mat4x4 Transform2DComponent::transform(){
		glm::mat4x4 transform = glm::translate(glm::mat4x4(1.0f), position);
		transform = glm::rotate(transform, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		transform = glm::rotate(transform, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, scaling);
		return transform;
	}
}