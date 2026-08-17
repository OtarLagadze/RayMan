/**
 *    author:  otuka
 *    created: July 11, 2026 1:03 PM
**/

#include "raylib.h"
#include "raymath.h"
#include "Globals.h"
#include "Box.h"
#include "Ray.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Cell.h"
#include "Grid.h"
#include <algorithm>

int PRECISION[16] = {1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15, 18, 20, 24, 30, 36};

int32_t main() {
    int FPS = 300;
    int grid_resolution = 4;

    Vector2 click;

    InitWindow(screen_width, screen_height, "rect raycaster");

    SetTargetFPS(FPS);
    Grid grid(PRECISION[grid_resolution]);

    player = {screen_width / 2, screen_height / 2};
    Enemy enemy = {screen_width / 2, screen_height / 2};

    int counter = 0;
    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        //updating window
        Vector2 origin = {(float)screen_width / 2, (float)screen_height / 2};

        grid_resolution= std::max(0, std::min(grid_resolution - (int)GetMouseWheelMove(), 15));
        grid = Grid(PRECISION[grid_resolution]);

        //updating border
        float margin = 100;
        float bw = screen_width - 2 * margin;
        float bh = screen_height - 2 * margin;
        float bx = (screen_width - bw) / 2;
        float by = (screen_height - bh) / 2;
        Box boundary(bx, by, bw, bh, true);

        //drawing
        ClearBackground(WHITE);
        BeginDrawing();
            boundary.draw();

            grid.draw();

            //drawing boxes
            Vector2 mouse = GetMousePosition();
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                click.x = mouse.x;
                click.y = mouse.y;
            } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                DrawRectangle(std::min(click.x, mouse.x), std::min(click.y, mouse.y), std::abs(click.x - mouse.x), std::abs(click.y - mouse.y), BLACK);
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
                bool hollow = IsMouseButtonReleased(MOUSE_BUTTON_RIGHT);
                boxes.push_back(Box(std::min(click.x, mouse.x), std::min(click.y, mouse.y), std::abs(click.x - mouse.x), std::abs(click.y - mouse.y), hollow));
            }
            for (Box &box : boxes) box.draw();
            boxes.push_back(boundary);

            //player actions
            if (IsKeyDown(KEY_W)) player.move({0, -1});
            if (IsKeyDown(KEY_S)) player.move({0, 1});
            if (IsKeyDown(KEY_A)) player.move({-1, 0});
            if (IsKeyDown(KEY_D)) player.move({1, 0});
            if (IsKeyPressed(KEY_SPACE)) player.shoot();

            player.update_angle(mouse);
            //player.cast_rays(20, 400);
            player.draw();

            
            if (!enemy.is_dead()) {
                //enemy.move(player);
                //enemy.npc.draw();
            }
            //enemy.cast_rays(20, 400);

            for (Bullet &blt : bullets) {
                //blt.trajectory.draw();
                blt.move();
                blt.draw();
            }
            while (!bullets.empty() && bullets.back().counter <= 0) bullets.pop_back();

            boxes.pop_back();
            DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

