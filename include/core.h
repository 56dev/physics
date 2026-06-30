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
class QuadTreeNode {
    private:
        bool discovered; //this is used for dfs when clearing;
    public:
        std::size_t capacity;
        Rectangle bounds; 
        QuadTreeNode* parent;
        QuadTreeNode* upper_left;
        QuadTreeNode* upper_right;
        QuadTreeNode* lower_right;
        QuadTreeNode* lower_left;
        bool divided;
        bool leaf;
        std::vector<Body*> bodies;
        QuadTreeNode(std::size_t, Rectangle);
        QuadTreeNode(std::size_t, Rectangle, QuadTreeNode*);
        bool insert_all(std::vector<Body>&);
        bool insert(Body* body);
        void subdivide();
        

};
void clear_quad_tree(QuadTreeNode* node);
Vector2Dir vector_components_to_vector_mag_and_dir(Vector2 vi);
Vector2 vector_mag_and_dir_to_vector_components(Vector2Dir vi);

namespace Debug {

    std::vector<Body> generate_random_bodies(Rectangle bounds, std::size_t n, float v_mag, float dt);
    void draw_quad_tree_nodes(QuadTreeNode* root);
}
