
#include "EgorkaEngineCore/Camera.hpp"
#include <glm/trigonometric.hpp>

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
        update_view_matrix();
	}
	void Camera::set_rotation(const glm::vec3& _rotation)
	{
        rotation = _rotation;
        update_view_matrix();
	}
	void Camera::set_projection_mode(const Projection _projection_mode)
	{
        projection_mode = _projection_mode;
        update_view_matrix();
	}
	void Camera::set_position_rotation(const glm::vec3& _position, const glm::vec3& _rotation)
	{
        rotation = _rotation;
        position = _position;
        update_view_matrix();
	}

    void Camera::update_view_matrix()
    {
        float rotate_in_radians_x = glm::radians(-rotation.x);
        glm::mat4 rotate_matrix_x(1, 0,                         0,                        0,
                                  0, cos(rotate_in_radians_x),  sin(rotate_in_radians_x), 0,
                                  0, -sin(rotate_in_radians_x), cos(rotate_in_radians_x), 0,
                                  0, 0,                         0,                        1);

        float rotate_in_radians_y = glm::radians(-rotation.y);
        glm::mat4 rotate_matrix_y(cos(rotate_in_radians_y), 0, -sin(rotate_in_radians_y), 0,
                                  0,                        1, 0,                         0,
                                  sin(rotate_in_radians_y), 0, cos(rotate_in_radians_y),  0,
                                  0,                        0, 0,                         1);

        float rotate_in_radians_z = glm::radians(-rotation.z);
        glm::mat4 rotate_matrix(cos(rotate_in_radians_z), sin(rotate_in_radians_z), 0, 0,
                               -sin(rotate_in_radians_z), cos(rotate_in_radians_z), 0, 0,
                                0,                        0,                        1, 0,
                                0,                        0,                        0, 1);

        glm::mat4 translate_matrix(1,            0,             0,           0,
                                   0,            1,             0,           0,
                                   0,            0,             1,           0,
                                   -position[0], -position[1], -position[2], 1);

        view_matrix = rotate_matrix_y * rotate_matrix_x * translate_matrix;
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
}