// goblock
#include "Component.h"
#include "GameScene.h"
#include "Setup.h"
#include "System.h"

int main() {
    TraceLog(LOG_INFO, "Starting GoBlock...");

    // Initialize game
    goblock::game::GameScene game_scene{};

    flecs::world game_world{};
    flecs::entity ball{};
    flecs::entity player{};
    game_scene.init(game_world, ball, player);

    // Start the game process
    InitWindow(goblock::setup::SCREEN_WIDTH, goblock::setup::SCREEN_HEIGHT,
            goblock::setup::GAME_NAME.c_str());
    SetTargetFPS(60);

    goblock::setup::game_screen = goblock::setup::GameScreen::GAME;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Render ball
        const auto* position_ball = ball.get<goblock::component::Position>();
        const auto* radius_ball = ball.get<goblock::component::SizeCircle>();
        const auto* velocity_ball = ball.get<goblock::component::Velocity>();

        DrawCircle(
                position_ball->x, position_ball->y, radius_ball->radius, WHITE);

        ball.set<goblock::component::Position>({
                position_ball->x + velocity_ball->x,
                position_ball->y + velocity_ball->y,
        });

        // Render player
        const auto* position_player =
                player.get<goblock::component::Position>();
        const auto* size_player =
                player.get<goblock::component::SizeRectangle>();
        const auto* velocity_player =
                player.get<goblock::component::Velocity>();

        DrawRectangle(position_player->x, position_player->y,
                size_player->width, size_player->height, DARKBLUE);

        player.set<goblock::component::Position>({
                position_player->x + velocity_player->x,
                position_player->y + velocity_player->y,
        });

        EndDrawing();
    }

    // Cleanup
    game_scene.cleanup();

    return 0;
}
