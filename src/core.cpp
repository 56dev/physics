#include <raylib.h>
#include <raymath.h>
#include <cmath>
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
    velocity {p_vel},
    acceleration {p_accel}
     {

    previous_position = Vector2Subtract(position, Vector2Scale(p_vel, dt));
}
Vector2 Body::get_velocity(float dt) {
    return Vector2Scale((Vector2Subtract(position, previous_position)), 1.0f/dt);
}

Vector2Dir vector_components_to_vector_mag_and_dir(Vector2 vi){
    Vector2Dir vr{0, 0};
    vr.magnitude = Vector2Length(vi);
    vr.theta = std::atan2f(vi.y, vi.x);
    return vr;
}

Vector2 vector_mag_and_dir_to_vector_components(Vector2Dir vi) {
    Vector2 vr{0, 0};
    vr.x = vi.magnitude * std::cos(vi.theta);
    vr.y = vi.magnitude * std::sin(vi.theta);
    return vr;
}
