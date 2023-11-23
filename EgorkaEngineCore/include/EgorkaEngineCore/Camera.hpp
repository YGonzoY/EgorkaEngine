
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
		void set_far_clip_plane(const float _far);
		void set_near_clip_plane(const float _near);
		void set_viewport_size(const float _width, const float _height);
		void set_field_of_view(const float _fov);

		const glm::mat4& get_view_matrix();
		const glm::mat4& get_projection_matrix() const { return projection_matrix; }
		const float get_far_clip_plane() const { return far_clip_plane; }
		const float get_near_clip_plane() const { return near_clip_plane; }
		const float get_field_of_view() const { return field_of_view; }

		void move_forward(const float delta);
		void move_right(const float delta);
		void move_up(const float delta);

		const glm::vec3& get_camera_position() const { return position; }
		const glm::vec3& get_camera_rotation() const { return rotation; }

		void add_movement_and_rotation(const glm::vec3& movement_delta,
			const glm::vec3& rotation_delta);

	private:

		void update_view_matrix();
		void update_projection_matrix();

		glm::vec3 direction;
		glm::vec3 right;
		glm::vec3 up;

		float far_clip_plane{ 100.f };
		float near_clip_plane{ 0.1f };
		float viewport_width{ 800.f };
		float viewport_height{ 600.f };
		float field_of_view{ 60.f };

		static constexpr glm::vec3 world_up{ 0.f, 0.f, 1.f };
		static constexpr glm::vec3 world_right{ 0.f, -1.f, 0.f };
		static constexpr glm::vec3 world_forward{ 1.f, 0.f, 0.f };
		bool is_updating_view_matrix;

		Projection projection_mode;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::mat4 view_matrix;
		glm::mat4 projection_matrix;
	};
}