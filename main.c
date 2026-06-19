#include <raylib.h>

int main(void) {

    InitWindow(200, 100, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}
