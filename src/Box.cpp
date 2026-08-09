#include "Box.h"

Box::Box() {}

Box::Box(float x, float y, float w, float h, bool type) {
    this->rec = {x, y, w, h};
    this->origin = {(x + w) / 2.0f, (y + h) / 2.0f};
    this->hollow = type;
    this->vertecies = {{x, y}, {x + w, y}, {x, y + h}, {x + w, y + h}};
}

void Box::draw() {
    if (this->hollow) {
        DrawRectangleLinesEx(rec, 1, BLACK);
    } else {
        DrawRectangleRec(rec, BLACK);
    }
}
