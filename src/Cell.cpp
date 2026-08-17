#include "raylib.h"
#include "Cell.h"
#include "Box.h"

Cell::Cell() {}

Cell::Cell(int row, int col, float cell_size) {
    index.x = row;
    index.y = col;

    size = cell_size; 

    container = Box(row * cell_size, col * cell_size, cell_size, cell_size, true);
    position.x = row * cell_size;
    position.y = col * cell_size;
}

void Cell::draw() {
    container.draw();
}
