#pragma once
#ifndef MESHVIEW_CAMERA_B9A22093_7B3A_49A5_B013_8935B9AEAEE6
#define MESHVIEW_CAMERA_B9A22093_7B3A_49A5_B013_8935B9AEAEE6

#include <Eigen/Core>

#include <cmath>

#include "meshview/common.hpp"

namespace meshview {

class Camera {
    public:
        // Construct camera with given params
        explicit Camera(
               const Vector3f& center_of_rot = Eigen::Vector3f(0.f, 0.f, 0.f),
               const Vector3f& world_up = Eigen::Vector3f(0.f, 1.f, 0.f),
               float dist_to_center = 3.f,
               float yaw = -M_PI/2,
               float pitch = 0.0f,
               float roll = 0.0f,
               float fovy = M_PI / 4.f,
               float aspect = 5.f / 3.f,
               float z_close = 0.01f,
               float z_far = 1e3f);

        // Get camera position
        inline Vector3f get_pos() const { return pos; }

        // Update view matrix, call after changing any view parameter
        void update_view();

        // Update proj matrix, call after changing any projection parameter
        void update_proj();

        // Handlers
        void rotate_with_mouse(float xoffset, float yoffset);
        void roll_with_mouse(float xoffset, float yoffset);
        void pan_with_mouse(float xoffset, float yoffset);
        void zoom_with_mouse(float amount);

        // Reset the view
        void reset_view();
        // Reset the projection
        void reset_proj();

        // * Camera matrices
        // View matrix: global -> view coords
        Matrix4f view;
        // Projection matrix: view -> clip coords (perspective)
        Matrix4f proj;

        // Camera mouse control options
        float pan_speed = .0015f, rotate_speed = .008f, scroll_factor = 1.1f;

        // * Projection parameters
        // Field of view, aspect ratio
        float fovy, aspect;
        // Clip distances
        float z_close, z_far;

        // * View parameters
        // Center of rotation
        Vector3f center_of_rot;
        // Normalized direction vectors
        Vector3f front, up, world_up;
        // Distance to cor
        float dist_to_center;

        // Euler angles, for mouse control
        float yaw, pitch, roll;
    private:
        // For caching only; right = front cross up; pos = cor - d2c * front
        Vector3f pos, right;
};

}  // namespace meshview

#endif  // ifndef MESHVIEW_CAMERA_B9A22093_7B3A_49A5_B013_8935B9AEAEE6
