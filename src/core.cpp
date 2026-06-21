#include <raylib.h>
#include <raymath.h>
#include "core.h"
void Body::update_position(float dt) {
    Vector2 tp = position;
    position.x = 2*position.x - previous_position.x + acceleration.x * dt*dt;
    position.y = 2*position.y - previous_position.y + acceleration.y * dt*dt;
    velocity.x = (position.x - previous_position.x) / dt;
    velocity.y = (position.y - previous_position.y) / dt;
    previous_position = tp;
}
Body::Body(
        Vector2 p_pos, 
        Vector2 p_vel, 
        Vector2 p_accel, 
        float dt) 
    : position{p_pos}, 
    acceleration {p_accel}
    velocity {p_vel} {

    previous_position = Vector2Subtract(position, Vector2Scale(p_vel, dt));
};
float Body::get_velocity(float dt) {
    return (position - previous_position) / dt;
}

