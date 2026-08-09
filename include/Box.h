#pragma once
#include "raylib.h"
#include <vector>

struct Box {
    Rectangle rec;
    Vector2 origin;
    bool hollow = false;

    std::vector<Vector2> vertecies;

    Box();
    Box(float x, float y, float w, float h, bool type);

    void draw();
};
