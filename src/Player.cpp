#include "Player.h"
#include "Box.h"
#include "Ray.h"
#include "Bullet.h"
#include "Globals.h"
#include "raymath.h"

Player::Player() {};

Player::Player(int x, int y) {
    pos.x = static_cast<float>(x);
    pos.y = static_cast<float>(y);
    dir = {0, 0};
}

void Player::draw() {
    DrawCircle(pos.x, pos.y, radius, RED);
    ray(pos, dir, 1000, true).draw();
}

void Player::update_angle(Vector2 mouse) {
    dir = Vector2Normalize(mouse - pos);
    Vector2 unit = {1, 0};
    angle = Vector2Angle(unit, dir);
}

void Player::shoot() {
    bullets.push_front(Bullet(pos, dir));
}

void Player::move(Vector2 dir) {
    for (Box &box : boxes) {
        Vector2 new_pos = pos;
        new_pos.x += dir.x * speed * dt;
        if (
                CheckCollisionCircleLine(new_pos, radius, box.vertecies[0], box.vertecies[1]) ||
                CheckCollisionCircleLine(new_pos, radius, box.vertecies[0], box.vertecies[2]) ||
                CheckCollisionCircleLine(new_pos, radius, box.vertecies[3], box.vertecies[1]) ||
                CheckCollisionCircleLine(new_pos, radius, box.vertecies[3], box.vertecies[2])
           ) {
            dir.x = 0;
        }
        new_pos = pos;
        new_pos.y += dir.y * speed * dt;
        if (
                CheckCollisionCircleLine(new_pos, radius, box.vertecies[0], box.vertecies[1]) ||
                CheckCollisionCircleLine(new_pos, radius, box.vertecies[0], box.vertecies[2]) ||
                CheckCollisionCircleLine(new_pos, radius, box.vertecies[3], box.vertecies[1]) ||
                CheckCollisionCircleLine(new_pos, radius, box.vertecies[3], box.vertecies[2])
           ) {
            dir.y = 0;
        }
    }
    pos = pos + dir * speed * dt;
}
