#pragma once
#include "raylib.h"
#include "Box.h"

struct Cell {
    float size;
    Vector2 index, position;
    Box container;

    Cell();
    Cell(int row, int col, float cell_size);

    void draw();
};
