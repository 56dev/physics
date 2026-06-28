#pragma once
#include <raylib.h>
#include <vector>
#define PHYSICS_DT (1.0f / 60.0f)
#define G_ACCEL 9.81f
struct Vector2Dir {
    float magnitude; //m
    float theta; //rad
};

class Body {
    private:
        Vector2 previous_position;
    public:
        Vector2 position; //m
        Vector2 velocity; //m/s
        Vector2 acceleration; //m/s^2
        float mass;
        float radius;
        std::vector<Vector2Dir> forces;
        Body(Vector2 p_pos, Vector2 p_vel, float p_mass, float p_radius, float dt); 
        void update_position(float dt);
        void reset_acceleration();
        void apply_gravity();
        float get_speed();
        float get_kinetic_energy();
        float get_potential_energy();
        float get_potential_energy_with_reference_height(float h);
        void get_collisions(std::vector<Body>);
        void apply_force(Vector2Dir force);
};
class Barrier {
    public:
        Vector2 start;
        Vector2 end;
        float restitution_factor;
        Barrier(Vector2 p_start, Vector2 p_end, float p_rf);
};

Vector2Dir vector_components_to_vector_mag_and_dir(Vector2 vi);
Vector2 vector_mag_and_dir_to_vector_components(Vector2Dir vi);
