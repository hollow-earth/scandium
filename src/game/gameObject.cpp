#include "gameObject.hpp"
#include <iostream>

namespace scandium {
	void Transform2DComponent::rotate(const float theta){
		const float sin = glm::sin(theta);
		const float cos = glm::cos(theta);
		rotationMatrix = {{cos, sin}, {-sin, cos}};
	}

	//TODO test this, I'm not sure about the semantics
	void Transform2DComponent::scale(glm::mat2x2 scaleMat){
		scaleMatrix = std::move(scaleMat);
	}

	void Transform2DComponent::scale(float scaling){
		scaleMatrix = {{scaling, 0.0f}, {0.0f, scaling}};
	}

	void Transform2DComponent::scale(float x_scaling, float y_scaling){
		scaleMatrix = {{x_scaling, 0.0f}, {0.0f, y_scaling}};
	}

	void Transform2DComponent::translate(float x_translation, float y_translation){
		position = {position.x + x_translation, position.y + y_translation};
	}

	glm::mat2 Transform2DComponent::transform(){ 
		return rotationMatrix * scaleMatrix;
	}

	//TODO implement a flip function that does (x,y) -> (-x,y)
	//void::Transform2DComponent::flip_x()
}