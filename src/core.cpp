#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <cstddef>
#include <numbers>
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
        float p_radius,
        float dt) 
    : position{p_pos}, 
    velocity {p_vel},
    mass {p_mass},
    radius {p_radius},
    acceleration {(Vector2){0,0}}

     {

    previous_position = Vector2Subtract(position, Vector2Scale(p_vel, dt));
}
float Body::get_speed() {
    return Vector2Length(velocity);
}
void Body::apply_gravity() {
    acceleration.y -= G_ACCEL;
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
void Body::apply_force(Vector2Dir force) {
    Vector2 fv = vector_mag_and_dir_to_vector_components(force);
    acceleration = Vector2Add(acceleration, Vector2Scale(fv, 1.0f / mass));
}
void Body::reset_acceleration(){
    acceleration = (Vector2){0, 0};
}

Barrier::Barrier(
            Vector2 p_start,
            Vector2 p_end,
            float p_rf 
        ) 
    : start {p_start},
    end {p_end},
    restitution_factor {p_rf} {}

QuadTreeNode::QuadTreeNode(std::size_t p_capacity, Rectangle p_bounds) : 
    capacity {p_capacity},
    bounds {p_bounds},
    parent {NULL},
    upper_left {NULL},
   upper_right {NULL},
  lower_right {NULL},
 lower_left {NULL},
divided {false},
       leaf {true} 

    {

}

QuadTreeNode::QuadTreeNode(std::size_t p_capacity, Rectangle p_bounds, QuadTreeNode* p_parent) :
    capacity {p_capacity},
    bounds {p_bounds},
    parent {p_parent},
    upper_left {NULL},
    upper_right {NULL},
    lower_right {NULL},
    lower_left {NULL},
    divided {false},
    leaf {true} {}
bool QuadTreeNode::insert_all(std::vector<Body>& bodies) {
    bool ret = true;
    for(std::size_t i = 0; i < bodies.size(); ++i) {
        if(insert(&bodies[i])) ret = false;
    }
    return ret;
}
bool QuadTreeNode::insert(Body* body) {
    if(!CheckCollisionCircleRec(body->position, body->radius, bounds)) {
        //unable to insert the body
        return false;
    }
    if(bodies.size() < capacity && divided == false) {
        bodies.push_back(body);
        return true;
    }
    if(divided == false) {
        subdivide();
    }
    if(upper_left->insert(body) | upper_right->insert(body) | lower_right->insert(body) | lower_left->insert(body)) return true;
    return false;
}

void clear_quad_tree(QuadTreeNode* node) {    
    if(node == NULL) {
        return;
    }
    clear_quad_tree(node->upper_left);
    delete node->upper_left;
    node->upper_left = NULL;
    clear_quad_tree(node->upper_right);
    delete node->upper_right;
    node->upper_right = NULL;
    clear_quad_tree(node->lower_right);
    delete node->lower_right;
    node->lower_right = NULL;
    clear_quad_tree(node->lower_left);
    delete node->lower_left;
    node->lower_left = NULL;
    
    node->divided = false;
    node->leaf = true;
}
void QuadTreeNode::subdivide() {
    upper_left = new QuadTreeNode(capacity, (Rectangle){bounds.x, bounds.y, bounds.width / 2, bounds.height / 2}, this);
    upper_right = new QuadTreeNode(capacity, (Rectangle){bounds.x + bounds.width/2, bounds.y, bounds.width / 2, bounds.height / 2}, this);
    lower_right = new QuadTreeNode(capacity, (Rectangle){bounds.x + bounds.width/2, bounds.y + bounds.height/2, bounds.width / 2, bounds.height / 2}, this);
    lower_left = new QuadTreeNode(capacity, (Rectangle){bounds.x, bounds.y + bounds.height/2, bounds.width / 2, bounds.height / 2}, this);
    for(std::size_t i = 0; i < bodies.size(); ++i) {
       Body* body = bodies[i];
       upper_left->insert(body);
       upper_right->insert(body);
       lower_right->insert(body);
       lower_left->insert(body);
    }
    bodies.clear();
    divided = true;
    leaf = false;
}

std::vector<Body> Debug::generate_random_bodies(Rectangle bounds, std::size_t n, float v_mag, float dt) {
    std::vector<Body> ret;
    for(std::size_t i = 0; i < n; ++i) {
        Vector2 p;
        Vector2 v;
        float angle = GetRandomValue(0, 359) * std::numbers::pi / 180.0f;
        p.x = GetRandomValue(bounds.x + 1, bounds.x + bounds.width - 1);
        p.y = GetRandomValue(bounds.y + 1, bounds.y + bounds.height - 1);
        
        v.x = v_mag * std::cos(angle);
        v.y = v_mag * std::sin(angle);
        ret.push_back(Body(p, v, 1, 3, dt));
    }
    return ret;
}

void Debug::draw_quad_tree_nodes(QuadTreeNode* root) {
    DrawRectangleLinesEx(root->bounds, 1.0f, RED);
    if(root->divided == true) {
        draw_quad_tree_nodes(root->upper_left);
        draw_quad_tree_nodes(root->upper_right);
        draw_quad_tree_nodes(root->lower_right);
        draw_quad_tree_nodes(root->lower_left);
    }
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

