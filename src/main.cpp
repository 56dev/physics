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

    Body body{CENTER, (Vector2){30.0f, 0}, (Vector2){30.0f, 0}, PHYSICS_DT};
    float time_accum = 0.0f;
    Vector2 tv[] = {
        {1, 0},
        {0, 2},
        {3, 3}
    };
    for(int i = 0; i < 3; ++i) {
        Vector2Dir vr = vector_components_to_vector_mag_and_dir(tv[i]);
        TraceLog(LOG_INFO, TextFormat("(%.5f m, %.5f m) is %.5f m, %.5f rad", tv[i].x, tv[i].y, vr.magnitude, vr.theta));
    }
    Vector2Dir tv2[] = {
        {1, std::numbers::pi},
        {2, std::numbers::pi/2},
        {3, 0}
    };
    for(int i = 0; i < 3; ++i) {
        Vector2 vr = vector_mag_and_dir_to_vector_components(tv2[i]);
        TraceLog(LOG_INFO, TextFormat("%.5f m [%.5f rad] is (%.5f m, %.5f m)", tv2[i].magnitude, tv2[i].theta, vr.x, vr.y));
    }
    while (!WindowShouldClose())
    {
        time_accum += GetFrameTime();
        float scale = BOILERPLATE_adjust_mouse_to_scale(GS_W, GS_H);
        while(time_accum >= PHYSICS_DT) {
            body.update_position(PHYSICS_DT);
            time_accum -= PHYSICS_DT;

        }
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            DrawCircleV(body.position, 3.0f, BLACK);
        EndTextureMode();
        BOILERPLATE_draw_to_screen(target, GS_W, GS_H, scale);
    }

    CloseWindow();

    return 0;
}
