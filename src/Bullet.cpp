#include "Bullet.h"
#include "Box.h"
#include "Globals.h"
#include "raymath.h"

std::deque<Bullet> bullets;

Bullet::Bullet(Vector2 start_point, Vector2 aim) {
    dir = aim;
    pos = start_point;
    trajectory = ray(start_point, dir, length, true);
}

void Bullet::move() {
    int sub_steps = 20;
    float cdt = dt;
    float spd = speed / sub_steps;
    for (int step = 1; step <= sub_steps; step++) {
        for (Box &box : boxes) {
            Vector2 new_pos = pos;
            new_pos.x += dir.x * spd * cdt;
            bool collision = false;
            if (
                    CheckCollisionCircleLine(new_pos, radius, box.vertecies[0], box.vertecies[1]) ||
                    CheckCollisionCircleLine(new_pos, radius, box.vertecies[0], box.vertecies[2]) ||
                    CheckCollisionCircleLine(new_pos, radius, box.vertecies[3], box.vertecies[1]) ||
                    CheckCollisionCircleLine(new_pos, radius, box.vertecies[3], box.vertecies[2])
               ) {
                dir.x *= -1;
                collision = true;
            }
            new_pos = pos;
            new_pos.y += dir.y * spd * cdt;
            if (
                    CheckCollisionCircleLine(new_pos, radius, box.vertecies[0], box.vertecies[1]) ||
                    CheckCollisionCircleLine(new_pos, radius, box.vertecies[0], box.vertecies[2]) ||
                    CheckCollisionCircleLine(new_pos, radius, box.vertecies[3], box.vertecies[1]) ||
                    CheckCollisionCircleLine(new_pos, radius, box.vertecies[3], box.vertecies[2])
               ) {
                dir.y *= -1;
                collision = true;
            }
            if (collision) {
                counter -= 1;
                break;
            }
        }
        pos = pos + dir * spd * cdt;
    }
}

void Bullet::draw() {
    DrawCircle(pos.x, pos.y, radius, PURPLE);
}

