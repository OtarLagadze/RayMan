#pragma once
#include "raylib.h"
#include "Ray.h"
#include <deque>

struct Bullet {
    Vector2 pos, dir;
    ray trajectory;
    float length = 800;
    float speed = 1000;
    float radius = 5;
    int counter = 5;

    Bullet(Vector2 start_point, Vector2 aim);

    void move();
    void draw();
};

extern std::deque<Bullet> bullets;
