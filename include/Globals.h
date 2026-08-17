#pragma once
#include "raylib.h"
#include "Player.h"
#include <vector>

struct Box;

extern const int screen_width;
extern const int screen_height;

extern float dt;
extern Player player;
extern std::vector<Box> boxes;

