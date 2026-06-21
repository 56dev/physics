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

