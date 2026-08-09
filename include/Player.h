#pragma once
#include "raylib.h"

struct Player {
    Vector2 pos, dir;
    float speed = 200;
    float radius = 20;
    float angle = 0;

    Player();
    Player(int x, int y);

    void draw();
    void update_angle(Vector2 mouse);
    void shoot();
    void move(Vector2 move_dir);
};
