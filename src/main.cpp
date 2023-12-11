#include "main.h"

int main()
{
    TraceLog(LOG_TRACE, "initialize game...");

    flecs::world game_worlds{};

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME.c_str());
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 100, WHITE);

        EndDrawing();
    }

    CloseWindow();

    TraceLog(LOG_TRACE, "deinitialize game...");

    return 0;
}
