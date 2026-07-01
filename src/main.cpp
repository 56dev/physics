#include <raylib.h>
#include <vector>
#include <cstddef>
#include "boilerplate.h"
#include "core.h"
#include "draw.h"
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
    //SetConfigFlags(FLAG_WINDOW_TOPMOST);
    
    target = BOILERPLATE_init(GS_W, GS_H, "physics");
    SetTargetFPS(60);

    QuadTreeNode root = QuadTreeNode(4uz, (Rectangle){0, 0, GS_W, GS_H});
    std::vector<Barrier> barriers;
    std::vector<Body> rbodies = Debug::generate_random_bodies((Rectangle){0, 0, GS_W, GS_H}, 4, 3, PHYSICS_DT);
    rbodies.push_back(Body((Vector2){100, 200}, (Vector2){0, 0}, 1, (Rectangle){-50, -50, 100, 100}, PHYSICS_DT));
    /*rbodies.push_back(
            Body(
                (Vector2){0, 500}, Vector2(0, 0), 1, (Line){(Vector2){0, 0}, (Vector2){1000, 0}}, PHYSICS_DT
                )
            );*/
    line_world_with_barriers(barriers, (Vector2){0,0}, GS_W, GS_H);
    float time_accum = 0.0f;
    while (!WindowShouldClose())
    {
        time_accum += GetFrameTime();
        float scale = BOILERPLATE_adjust_mouse_to_scale(GS_W, GS_H);
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);
        while(time_accum >= PHYSICS_DT) {
            for(std::size_t i = 0; i < rbodies.size(); ++i) {
                rbodies[i].update_position(PHYSICS_DT);

            }
            time_accum -= PHYSICS_DT;

        }
            root.insert_all(rbodies);
            Debug::draw_quad_tree_nodes(&root);
            clear_quad_tree(&root);

            draw_bodies(rbodies);
        /*
            DrawText(TextFormat("Energy: %.2f J", body.get_kinetic_energy()), 10, 10, 40, BLACK);
            DrawText(TextFormat("Velocity: %.2f m/s", body.get_speed()), 10, 60, 40, BLACK);
            DrawCircleV(body.position, body.radius, BLACK);
            */
            
            
        EndTextureMode();
        BOILERPLATE_draw_to_screen(target, GS_W, GS_H, scale);
    }

    CloseWindow();

    return 0;
}
