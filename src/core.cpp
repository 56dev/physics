#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <cstddef>
#include "core.h"
void Body::update_position(float dt) {
    Vector2 tp = position;
    position.x = 2*position.x - previous_position.x + acceleration.x * dt*dt;
    position.y = 2*position.y - previous_position.y + acceleration.y * dt*dt;
    previous_position = tp;
    velocity.x = (position.x - previous_position.x) / dt;
    velocity.y = (position.y - previous_position.y) / dt;
}
Body::Body(
        Vector2 p_pos, 
        Vector2 p_vel, 
        float p_mass,
        float dt) 
    : position{p_pos}, 
    velocity {p_vel},
    mass {p_mass}

     {

    previous_position = Vector2Subtract(position, Vector2Scale(p_vel, dt));
}
float Body::get_speed() {
    return Vector2Length(velocity);
}

float Body::get_kinetic_energy() {
    float v = Vector2Length(velocity);
    return 0.5 * mass * v * v;
}

float Body::get_potential_energy_with_reference_height(float ref) {
    return mass * 9.81 * (position.y - ref);

}
float Body::get_potential_energy() {
    return Body::get_potential_energy_with_reference_height(0);
}
void Body::add_force(Vector2Dir force) {
    forces.push_back(force);
}
void Body::update_acceleration(){
    Vector2 total_force = {0, 0};
    for(std::size_t i = 0; i < forces.size(); ++i) {
        Vector2 fv = vector_mag_and_dir_to_vector_components(forces[i]);
        total_force = Vector2Add(total_force, fv);
    }
    Vector2 accel = Vector2Scale(total_force, 1.0f / mass);
    acceleration = accel;
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

