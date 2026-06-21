#pragma once
#include <raylib.h>
#define PHYSICS_DT (1.0f / 60.0f)
class Body {
    private:
        Vector2 previous_position;
    public:
        Vector2 position; //m
        Vector2 velocity; //m/s
        Vector2 acceleration; //m/s^2
        Body(Vector2 p_pos, Vector2 p_vel, Vector2 p_accel, float dt); 
        void update_position(float dt);
        Vector2 get_velocity(float dt);
};
struct Vector2Dir {
    float magnitude; //m
    float theta; //rad
};
Vector2Dir vector_components_to_vector_mag_and_dir(Vector2 vi);
Vector2 vector_mag_and_dir_to_vector_components(Vector2Dir vi);
