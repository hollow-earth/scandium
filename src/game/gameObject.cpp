#include "gameObject.hpp"
#include <iostream>

namespace scandium {
	void Transform2DComponent::scale(const float x_scaling, const float y_scaling, const float z_scaling){
		scaling = {x_scaling, y_scaling, z_scaling};
	}

	void Transform2DComponent::scale(const float scaling_factor){
		scaling = {scaling_factor, scaling_factor, scaling_factor};
	}
	// x = [-1, 1], y = [-1, 1], z = [0, 1]
	//TODO implement this?
	void Transform2DComponent::translate(const float x_translation, const float y_translation, const float z_translation){
		position = {position.x + x_translation, position.y + y_translation, position.z + z_translation};
	}

	void Transform2DComponent::rotate(const float theta_x, 
		const float theta_y, const float theta_z){ rotation = {theta_x, theta_y, theta_z}; }

	void Transform2DComponent::rotate(const float theta_z){ rotation.z = theta_z; }

	// Flip about the x-axis
	void Transform2DComponent::flip_x(){
		rotation.x += glm::pi<float>();
		//if (rotation.x >= glm::two_pi<float>()){
		//	rotation.x -= glm::two_pi<float>();
		//}
	}
	
	// Flip about the y-axis
	void Transform2DComponent::flip_y(){
		rotation.y += glm::pi<float>();
		//if (rotation.y >= glm::two_pi<float>()){
		//	rotation.y -= glm::two_pi<float>();
		//}
	}

	glm::mat4x4 Transform2DComponent::transform(){
		glm::mat4x4 transform = glm::translate(glm::mat4x4(1.0f), position);
		transform = transform * glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
		transform = glm::scale(transform, scaling);
		return transform;
	}
}