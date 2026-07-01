#include <raylib.h>
#include <raymath.h>
#include <cstddef>
#include "core.h"
#include <vector>
#include <variant>
void draw_body(Body& body) {
    if(std::holds_alternative<Circle>(body.shape)) {
        Circle s = std::get<Circle>(body.shape);
        DrawCircleV(Vector2Add(body.position, s.position), s.radius, BLACK);
    } else if(std::holds_alternative<Rectangle>(body.shape)) {
        Rectangle s = std::get<Rectangle>(body.shape);
        DrawRectangle(body.position.x + s.x, body.position.y + s.y, s.width, s.height, BLACK);
    } else if(std::holds_alternative<Line>(body.shape)) {
        Line s = std::get<Line>(body.shape);
        DrawLineV(Vector2Add(body.position, s.start), Vector2Add(body.position, s.end), BLACK);
    }
}

void draw_bodies(std::vector<Body>& bodies) {

    for(std::size_t i = 0; i < bodies.size(); ++i) {
        draw_body(bodies[i]);
    }
}
