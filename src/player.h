#pragma once

#include "raylib.h"

struct Player {
    Vector2 position;
    Color colour;
    float speed;
    float radius;
};
typedef struct Player Player;

Player new_default_player();

void update_player(Player *p);

void draw_player(const Player * const p);

