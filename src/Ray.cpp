#include "Ray.h"
#include "Box.h"
#include "Globals.h"
#include "raymath.h"

ray::ray() {}

ray::ray(Vector2 pos, Vector2 dir, float length, bool breakable) {
    this -> pos = pos;
    this -> dir = dir;
    this -> length = length;
    this -> break_length = length;
    this -> break_point = pos + dir * length;
    this -> breakable = breakable;
    cast();
}

float ray::get_intersection(Vector2 &surface_vector, Vector2 &collision_point) {
    float min_distance = length;
    Vector2 finish = pos + dir * length, intersection_point = finish;
    for (Box box : boxes) {
        if (CheckCollisionLines(pos, finish, box.vertecies[0], box.vertecies[1], &intersection_point) && intersection_point != pos && Vector2Distance(pos, intersection_point) < min_distance) min_distance = Vector2Distance(pos, intersection_point), collision_point = intersection_point, surface_vector = box.vertecies[1] - box.vertecies[0];
        if (CheckCollisionLines(pos, finish, box.vertecies[0], box.vertecies[2], &intersection_point) && intersection_point != pos && Vector2Distance(pos, intersection_point) < min_distance) min_distance = Vector2Distance(pos, intersection_point), collision_point = intersection_point, surface_vector = box.vertecies[2] - box.vertecies[0];
        if (CheckCollisionLines(pos, finish, box.vertecies[3], box.vertecies[1], &intersection_point) && intersection_point != pos && Vector2Distance(pos, intersection_point) < min_distance) min_distance = Vector2Distance(pos, intersection_point), collision_point = intersection_point, surface_vector = box.vertecies[1] - box.vertecies[3];
        if (CheckCollisionLines(pos, finish, box.vertecies[3], box.vertecies[2], &intersection_point) && intersection_point != pos && Vector2Distance(pos, intersection_point) < min_distance) min_distance = Vector2Distance(pos, intersection_point), collision_point = intersection_point, surface_vector = box.vertecies[2] - box.vertecies[3];
    }
    return min_distance;
}

void ray::cast() {
    Vector2 end_point = pos + dir * length, aim = dir, surface_vector;
    float curr = get_intersection(surface_vector, end_point);
    this -> break_length = curr;
    this -> break_point = end_point;

    if (breakable && length != curr) {
        surface_vector = Vector2Normalize(surface_vector);
        Vector2 incoming = Vector2Normalize(aim);
        aim = -1 * Vector2Reflect(incoming, surface_vector);
        this -> next = std::make_unique<ray>(end_point, aim, length - curr, true);
        this -> kills = this -> next -> kills;
    }

    if (CheckCollisionCircleLine(player.pos, player.radius, this -> pos, this -> break_point)) {
        this -> kills = true;
    }
}

void ray::draw() {
    ray *curr = this;
    while (curr != nullptr) {
        DrawCircle(curr -> break_point.x, curr -> break_point.y, 5, (kills ? BLACK : GREEN));
        DrawLineV(curr -> pos, curr -> break_point, (kills ? RED : BLUE));
        curr = curr -> next.get();
    }
}
