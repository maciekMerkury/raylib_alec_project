#include <stdio.h>

#include "player.h"
#include "raylib.h"
#include "raymath.h"

Player new_default_player()
{
    return (Player) {
        .position = { 0 },
        .colour = RED,
        .speed = 400.0,
        .radius = 50.0,
    };
}

void get_dir_input(Vector2 * const direction)
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) direction->x += 1;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) direction->x -= 1;
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) direction->y += 1;
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) direction->y -= 1;

    *direction = Vector2Normalize(*direction);
}

void update_player(Player *p)
{
    Vector2 dir_input = {0};
    get_dir_input(&dir_input);

    float delta = GetFrameTime();

    printf("input = [%f, %f]\tdelta = %f\t", dir_input.x, dir_input.y, delta);

    p->position.x += dir_input.x * delta * p->speed;
    p->position.y += dir_input.y * delta * p->speed;

    printf("position = [%f, %f]\n", p->position.x, p->position.y);
}

void draw_player(const Player * const p)
{
    DrawCircleV(p->position, p->radius, p->colour);
}

