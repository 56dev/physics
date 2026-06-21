#include <raylib.h>
#include "boilerplate.h"
int main(void) {

    RenderTexture2D target;
    const int GS_W = 1920;
    const int GS_H = 1080;
    target = BOILERPLATE_init(GS_W, GS_H, "physics");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float scale = BOILERPLATE_adjust_mouse_to_scale(GS_W, GS_H);

        BeginTextureMode(target);
            ClearBackground(RAYWHITE);

        EndTextureMode();
        BOILERPLATE_draw_to_screen(target, GS_W, GS_H, scale);
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
