
#include "EgorkaEngineCore/Camera.hpp"
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace EgorkaEngine
{

	Camera::Camera(const glm::vec3& _position, const glm::vec3& _rotation, const Projection _mode)
		: rotation(_rotation), position(_position), projection_mode(_mode)
	{
		update_view_matrix();
		update_projection_matrix();
	}

	void Camera::set_position(const glm::vec3& _position)
	{
        position = _position;
        is_updating_view_matrix = true;
	}
	void Camera::set_rotation(const glm::vec3& _rotation)
	{
        rotation = _rotation;
        is_updating_view_matrix = true;
	}
	void Camera::set_projection_mode(const Projection _projection_mode)
	{
        projection_mode = _projection_mode;
        is_updating_view_matrix = true;;
	}
	void Camera::set_position_rotation(const glm::vec3& _position, const glm::vec3& _rotation)
	{
        rotation = _rotation;
        position = _position;
        is_updating_view_matrix = true;
	}

    void Camera::update_view_matrix()
    {
        const float roll_in_radians = glm::radians(rotation.x);
        const float pitch_in_radians = glm::radians(rotation.y);
        const float yaw_in_radians = glm::radians(rotation.z);

        const glm::mat3 rotate_matrix_x(1, 0, 0,
            0, cos(roll_in_radians), sin(roll_in_radians),
            0, -sin(roll_in_radians), cos(roll_in_radians));

        const glm::mat3 rotate_matrix_y(cos(pitch_in_radians), 0, -sin(pitch_in_radians),
            0, 1, 0,
            sin(pitch_in_radians), 0, cos(pitch_in_radians));

        const glm::mat3 rotate_matrix_z(cos(yaw_in_radians), sin(yaw_in_radians), 0,
            -sin(yaw_in_radians), cos(yaw_in_radians), 0,
            0, 0, 1);

        const glm::mat3 euler_rotate_matrix = rotate_matrix_z * rotate_matrix_y * rotate_matrix_x;
        direction = glm::normalize(euler_rotate_matrix * world_forward);
        right = glm::normalize(euler_rotate_matrix * world_right);
        up = glm::cross(right, direction);

        view_matrix = glm::lookAt(position, position + direction, up);
    }

    void Camera::update_projection_matrix()
    {
        if (projection_mode == Projection::Perspective)
        {
            float r = 0.1f;
            float t = 0.1f;
            float f = 10;
            float n = 0.1f;
            projection_matrix = glm::mat4(n / r, 0, 0, 0,
                                          0, n / t, 0, 0,
                                          0, 0, (-f - n) / (f - n), -1,
                                          0, 0, -2 * f * n / (f - n), 0);
        }
        else
        {
            float r = 2;
            float t = 2;
            float f = 100;
            float n = 0.1f;
            projection_matrix = glm::mat4(1 / r, 0, 0, 0,
                                          0, 1 / t, 0, 0,
                                          0, 0, -2 / (f - n), 0,
                                          0, 0, (-f - n) / (f - n), 1);
        }
    }

    void Camera::move_forward(const float delta)
    {
        position += direction * delta;
        is_updating_view_matrix = true;
    }

    void Camera::move_right(const float delta)
    {
        position += right * delta;
        is_updating_view_matrix = true;
    }

    void Camera::move_up(const float delta)
    {
        position += up * delta;
        is_updating_view_matrix = true;
    }

    void Camera::add_movement_and_rotation(const glm::vec3& movement_delta,
        const glm::vec3& rotation_delta)
    {
        position += direction * movement_delta.x;
        position += right * movement_delta.y;
        position += up * movement_delta.z;
        rotation += rotation_delta;
        is_updating_view_matrix = true;
    }

    const glm::mat4& Camera::get_view_matrix()
    {
        if (is_updating_view_matrix)
        {
            update_view_matrix();
            is_updating_view_matrix = false;
        }
        return view_matrix;
    }
}