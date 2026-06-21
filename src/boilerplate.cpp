#include "boilerplate.h"
#include <raylib.h>
#include <raymath.h>
#define MIN(a,b) ((a) < (b) ? (a) : (b))

RenderTexture2D BOILERPLATE_init(int game_screen_width, int game_screen_height, const char *title) {

    SetConfigFlags( FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_WINDOW_MAXIMIZED);   

    InitWindow(game_screen_width, game_screen_height, title);
    InitAudioDevice();
    SetWindowMinSize(640, 360);
    SetTargetFPS(60);    
    RenderTexture2D target = LoadRenderTexture(game_screen_width, game_screen_height);
    SetTextureFilter(target.texture, TEXTURE_FILTER_TRILINEAR);
    return target;

}

float BOILERPLATE_adjust_mouse_to_scale(int game_screen_width, int game_screen_height) {
    float scale = MIN((float)GetScreenWidth()/game_screen_width, (float)GetScreenHeight()/game_screen_height);
    Vector2 mouse = GetMousePosition();
    Vector2 virtualMouse = { 0,0 };
    virtualMouse.x = (mouse.x - (GetScreenWidth() - (game_screen_width*scale))*0.5f)/scale;
    virtualMouse.y = (mouse.y - (GetScreenHeight() - (game_screen_height*scale))*0.5f)/scale;
    virtualMouse = Vector2Clamp(
        virtualMouse, 
        (Vector2){0, 0}, 
        (Vector2){ 
            (float)game_screen_width, 
            (float)game_screen_height} 
        );
    SetMouseOffset((-(GetScreenWidth() - (game_screen_width*scale))*0.5f),
                (-(GetScreenHeight() - (game_screen_height*scale))*0.5f));
    SetMouseScale(1/scale, 1/scale);
    return scale;
}

void BOILERPLATE_draw_to_screen(RenderTexture2D target, int game_screen_width, int game_screen_height, float scale) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(target.texture, 
        (Rectangle){ 
            0.0f, 0.0f, 
            (float)target.texture.width, 
            (float)-target.texture.height},
        (Rectangle){
            (GetScreenWidth() - ((float)game_screen_width*scale))*0.5f, 
            (GetScreenHeight() - ((float)game_screen_height*scale))*0.5f,
            (float)game_screen_width*scale, (float)game_screen_height*scale
        },
        (Vector2){0, 0}, 
        0,
        WHITE
        );        
    EndDrawing();
}
