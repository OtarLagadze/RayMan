#include "Grid.h"
#include "Globals.h"
#include "Cell.h"
#include <vector>
#include <algorithm>

Grid::Grid() {}

Grid::Grid(int prec) {
    float cell_size = std::__gcd(screen_width, screen_height) / prec;

    dimensions.x = screen_width / cell_size;
    dimensions.y = screen_height / cell_size;

    for (int i = 0; i < dimensions.x; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < dimensions.y; j++) {
            row.push_back(Cell(i, j, cell_size));
        }
        collection.push_back(row);
    }
}

void Grid::draw() {
    for (auto row : collection) {
        for (auto element : row) {
            element.draw();
        }
    }
}
