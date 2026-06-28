#include <raylib.h>
#include <vector>
#include <cstddef>
#include "boilerplate.h"
#include "core.h"
#include <numbers>
void line_world_with_barriers (std::vector<Barrier>& barriers, Vector2 origin, int GS_W, int GS_H) {
    Vector2 upleft = origin;
    Vector2 upright = {origin.x + GS_W, origin.y};
    Vector2 lowleft = {origin.x, origin.y + GS_H};
    Vector2 lowright = {origin.x + GS_W, origin.y + GS_H};
    barriers.push_back(Barrier(upleft, upright, 1));
    barriers.push_back(Barrier(upright, lowright, 1));
    barriers.push_back(Barrier(lowright, lowleft, 1));
    barriers.push_back(Barrier(lowleft, upleft, 1));
    
}
int main(void) {

    RenderTexture2D target;
    const int GS_W{1920};
    const int GS_H{1080};
    Vector2 CENTER{GS_W / 2, GS_H / 2};
    SetConfigFlags(FLAG_WINDOW_TOPMOST);
    target = BOILERPLATE_init(GS_W, GS_H, "physics");
    SetTargetFPS(60);

    Body body{CENTER, (Vector2){30.0f, 0}, 1, 2, PHYSICS_DT};
    std::vector<Barrier> barriers;
    line_world_with_barriers(barriers, (Vector2){0,0}, GS_W, GS_H);
    float time_accum = 0.0f;
    while (!WindowShouldClose())
    {
        time_accum += GetFrameTime();
        float scale = BOILERPLATE_adjust_mouse_to_scale(GS_W, GS_H);
        while(time_accum >= PHYSICS_DT) {
            body.apply_force((Vector2Dir){30.0f, 0});
            body.apply_gravity();
            body.update_position(PHYSICS_DT);
            body.reset_acceleration();
            time_accum -= PHYSICS_DT;

        }
        BeginTextureMode(target);
            DrawText(TextFormat("Energy: %.2f J", body.get_kinetic_energy()), 10, 10, 40, BLACK);
            DrawText(TextFormat("Velocity: %.2f m/s", body.get_speed()), 10, 60, 40, BLACK);
            ClearBackground(RAYWHITE);
            DrawCircleV(body.position, body.radius, BLACK);
            for(std::size_t i = 0; i < barriers.size(); ++i) {
                DrawLineEx(barriers[i].start, barriers[i].end, 3.0f, BLACK);
            }
        EndTextureMode();
        BOILERPLATE_draw_to_screen(target, GS_W, GS_H, scale);
    }

    CloseWindow();

    return 0;
}
