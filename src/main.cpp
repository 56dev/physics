#include <raylib.h>
#include "boilerplate.h"
#include "core.h"
#include <numbers>
int main(void) {

    RenderTexture2D target;
    const int GS_W{1920};
    const int GS_H{1080};
    Vector2 CENTER{GS_W / 2, GS_H / 2};
    target = BOILERPLATE_init(GS_W, GS_H, "physics");
    SetTargetFPS(60);

    Body body{CENTER, (Vector2){30.0f, 0}, 1, (Vector2){10, 10}, PHYSICS_DT};
    body.add_force((Vector2Dir){30.0f, 0});
    float time_accum = 0.0f;
    while (!WindowShouldClose())
    {
        time_accum += GetFrameTime();
        float scale = BOILERPLATE_adjust_mouse_to_scale(GS_W, GS_H);
        while(time_accum >= PHYSICS_DT) {
            body.update_acceleration();
            body.apply_gravity();
            body.update_position(PHYSICS_DT);
            time_accum -= PHYSICS_DT;

        }
        BeginTextureMode(target);
            DrawText(TextFormat("Energy: %.2f J", body.get_kinetic_energy()), 10, 10, 40, BLACK);
            DrawText(TextFormat("Velocity: %.2f m/s", body.get_speed()), 10, 60, 40, BLACK);
            ClearBackground(RAYWHITE);
            DrawRectangle(body.position.x - body.hitbox.x/2, body.position.y - body.hitbox.x/2, body.hitbox.x, body.hitbox.y, BLACK);
        EndTextureMode();
        BOILERPLATE_draw_to_screen(target, GS_W, GS_H, scale);
    }

    CloseWindow();

    return 0;
}
