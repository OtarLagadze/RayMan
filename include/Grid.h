#pragma once
#include "raylib.h"
#include "Cell.h"
#include <vector>

struct Grid {
    Vector2 dimensions;
    std::vector<std::vector<Cell>> collection;

    Grid();
    Grid(int prec);

    void draw();
};
