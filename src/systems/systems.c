#include "systems.h"

#include "raymath.h"

void
move_pos(Position* const pos, Velocity* const vel, int entity_count, float d_t)
{

    for (int i = 0; i < entity_count; i++) {
        pos[i] = Vector2Add(pos[i], Vector2Scale(vel[i], d_t));
    }
}
