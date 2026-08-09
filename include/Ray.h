#pragma once
#include "raylib.h"
#include <memory>

struct ray {
    Vector2 pos, dir, break_point;
    std::unique_ptr<ray> next = nullptr;
    bool breakable = false;
    bool kills = false;
    float length = 0.0f;
    float break_length = 0.0f;

    ray();
    ray(Vector2 pos, Vector2 dir, float length, bool breakable);

    float get_intersection(Vector2 &surface_vector, Vector2 &collision_point);
    void cast();
    void draw();
};
