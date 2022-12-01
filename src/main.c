#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "player.h"

int main()
{
    int screenW = 800;
    int screenH = 400;
    float speed = 5.0;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenW, screenH, "A raylib window");
    SetTargetFPS(60);

    Player p = new_default_player();

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            screenH = GetScreenHeight();
            screenW = GetScreenWidth();
        }

        update_player(&p);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            draw_player(&p);
            //DrawCircleV(position, 50, MAROON);
            //char *text = "This hopefully works";
            //int text_len = strlen(text);
            //int font_size = 20;
            //DrawText(text, screenW / 2 - text_len * font_size / 4, screenH / 2, font_size, BLACK);
        }
        EndDrawing();
    }


    CloseWindow();

    return 0;
}
