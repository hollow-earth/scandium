#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x2.hpp>
#include <glm/vec3.hpp>

namespace scandium{
	class Camera{
		public:
			void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);
			void setPerspectiveProjection(float fovy, float aspect, float near, float far);
			void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3{0.0f, -1.0f, 0.0f});
			void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3{0.0f, -1.0f, 0.0f}); // To be used to fixate on character later
			void setViewYXZ(glm::vec3 position, glm::vec3 rotation);
			const glm::mat4x4 getProjection() const {return projectionMatrix; }
			const glm::mat4x4 getView() const {return viewMatrix; }
		private:
			glm::mat4x4 projectionMatrix{1.0f};
			glm::mat4x4 viewMatrix{1.0f};
	};
}