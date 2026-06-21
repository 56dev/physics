#pragma once 
#include <raylib.h>
RenderTexture2D BOILERPLATE_init(int game_screen_width, int game_screen_height, const char *title);
float BOILERPLATE_adjust_mouse_to_scale(int game_screen_width, int game_screen_height);
void BOILERPLATE_draw_to_screen(RenderTexture2D target, int game_screen_width, int game_screen_height, float scale);
