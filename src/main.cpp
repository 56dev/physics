#include <raylib.h>
#include "boilerplate.h"
#include "core.h"
int main(void) {

    RenderTexture2D target;
    const int GS_W{1920};
    const int GS_H{1080};
    Vector2 CENTER{GS_W / 2, GS_H / 2};
    target = BOILERPLATE_init(GS_W, GS_H, "physics");
    SetTargetFPS(60);

    Body body{CENTER, (Vector2){30.0f, 0}, (Vector2){30.0f, 0}, PHYSICS_TIME_STEP};

    while (!WindowShouldClose())
    {
        float scale = BOILERPLATE_adjust_mouse_to_scale(GS_W, GS_H);
        body.update_position(PHYSICS_TIME_STEP);
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            DrawCircleV(body.position, 3.0f, BLACK);
        EndTextureMode();
        BOILERPLATE_draw_to_screen(target, GS_W, GS_H, scale);
    }

    CloseWindow();

    return 0;
}
