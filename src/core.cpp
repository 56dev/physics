#include <raylib.h>
#include <raymath.h>
#include "core.h"
void Body::update_position(float dt) {
    this->position = Vector2Add(this->position, Vector2Scale(this->velocity,dt));
}
