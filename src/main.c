#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ecs/ecs.h"
#include "raylib.h"
#include "components/components.h"

typedef enum {
    POSITION,
    VELOCITY,
} ComponentIds;

void
test_main()
{
    int s_w = 800;
    int s_h = 400;

    InitWindow(s_w, s_h, "raylib window");

    SetTargetFPS(60);

    Vector2 ballPosition = { (float)s_w/2, (float)s_h/2 };

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;


        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            DrawCircleV(ballPosition, 50, MAROON);
        }
        EndDrawing();
    }

    CloseWindow();
}

void
update_ball_position(Position *pos)
{
    if (IsKeyDown(KEY_RIGHT)) pos->position.x += 2.0f;
    if (IsKeyDown(KEY_LEFT)) pos->position.x -= 2.0f;
    if (IsKeyDown(KEY_UP)) pos->position.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN)) pos->position.y += 2.0f;
}

int
main()
{
    EcsState state = SHORT_ECS_INIT(32, sizeof(Position));

    EntityId ball_id = SHORT_INIT_ENTITY(&state, POSITION);

    int s_w = 800;
    int s_h = 400;

    {
        EntityQueryResult res = ECS_GET_ENTITY_COMPONENTS(&state, ball_id, POSITION); 

        // Debug asserts to make sure stuff works
        assert(res.component_type_count == 1);
        assert(res.component_indices[0] == POSITION);
        printf("state : %lu\n", state.components[0].element_size);
        printf("size = %lu\n", res.components[0].inner_size);
        assert(res.components[0].inner_size == sizeof(Position));


        Position *id_pos = res.components[0].data;
        id_pos->position = (Vector2) { (float)s_w/2, (float)s_h/2 };
    } // res is dropped here

    InitWindow(s_w, s_h, "another raylib window");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        // Normally one would query for more than one component
        Position *ball_pos = ECS_GET_ENTITY_COMPONENTS(&state, ball_id, POSITION).components[0].data;

        update_ball_position(ball_pos);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            DrawCircleV(ball_pos->position, 50, MAROON);
        }
        EndDrawing();
    }

    return 0;
}

