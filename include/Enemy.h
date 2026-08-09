#pragma once
#include "Player.h"
#include <vector>

struct Enemy {
    Player npc = {0, 0};
    Vector2 aim = {0, 0};

    Enemy(int x, int y);

    void cast_rays(int cnt, float length);
    void move(Player target);
    bool is_dead();
};

extern std::vector<Enemy> enemies;
