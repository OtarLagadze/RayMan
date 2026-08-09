#include "Enemy.h"
#include "Ray.h"
#include "Bullet.h"
#include "raymath.h"
#include <cmath>

std::vector<Enemy> enemies;

Enemy::Enemy(int x, int y) {
    npc = Player(x, y);
    npc.speed = 50;
};

void Enemy::cast_rays(int cnt, float length) {
    float theta = (float)2 * M_PI / cnt;
    for (int i = 0; i < cnt; i++) {
        Vector2 dir = {cos(theta * i), sin(theta * i)};
        ray(npc.pos, dir, length, true).draw();
    }
}

void Enemy::move(Player target) {
    int cnt = 124;
    float length = 256;
    float theta = (float)2 * M_PI / cnt;
    for (int i = 0; i < cnt; i++) {
        Vector2 dir = {cos(theta * i), sin(theta * i)};
        ray shot = ray(npc.pos, dir, length, false);
        if (shot.kills) {
            aim = Vector2Normalize((aim + shot.dir));
        }
        shot.draw();
    }
    npc.move(aim);
}

bool Enemy::is_dead() {
    for (auto& blt : bullets) {
        if (CheckCollisionCircles(npc.pos, npc.radius, blt.pos, blt.radius)) return true;
    }
    return false;
}
