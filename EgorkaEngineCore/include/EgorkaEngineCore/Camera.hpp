
#pragma once

#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace EgorkaEngine
{
	class Camera
	{
	public:
		enum class Projection
		{
			Perspective,
			Orthographic
		};

		Camera(const glm::vec3& _position = { 0, 0, 0 }, const glm::vec3& _rotation = {0,0,0}, const Projection _mode = Projection::Perspective);

		void set_position(const glm::vec3& _position);
		void set_rotation(const glm::vec3& _rotation);
		void set_projection_mode(const Projection _projection_mode);
		void set_position_rotation(const glm::vec3& _position, const glm::vec3& _rotation);

		glm::mat4 get_view_matrix() const { return view_matrix; }
		glm::mat4 get_projection_matrix() const { return projection_matrix; }

	private:

		void update_view_matrix();
		void update_projection_matrix();

		Projection projection_mode;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;
	};
}