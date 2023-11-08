
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

		const glm::mat4& get_view_matrix() const { return view_matrix; }
		const glm::mat4& get_projection_matrix() const { return projection_matrix; }

		void move_forward(const float delta);
		void move_right(const float delta);
		void move_up(const float delta);

		const glm::vec3& get_camera_position() const { return position; }
		const glm::vec3& get_camera_rotation() const { return rotation; }

		// movement_delta.x - forward, movement_delta.y - right, movement_delta.z - up
		// rotation_delta.x - roll, rotation_delta.y - pitch, rotation_delta.z - yaw
		void add_movement_and_rotatition(const glm::vec3& movement_delta,
			const glm::vec3& rotation_delta);

	private:

		void update_view_matrix();
		void update_projection_matrix();

		glm::vec3 direction;
		glm::vec3 right;
		glm::vec3 up;

		static constexpr glm::vec3 world_up{ 0.f, 0.f, 1.f };
		static constexpr glm::vec3 world_right{ 0.f, -1.f, 0.f };
		static constexpr glm::vec3 world_forward{ 1.f, 0.f, 0.f };

		Projection projection_mode;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;
	};
}