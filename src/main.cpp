// goblock
#include "Component.h"
#include "GameScene.h"
#include "Setup.h"
#include "System.h"

int main() {
    TraceLog(LOG_INFO, "Starting GoBlock...");

    // Initialize world, entity, object, etc
    flecs::world game_world{};
    flecs::entity ball{};
    flecs::entity player{};
    goblock::game::GameScene::init(game_world, ball, player);

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
                position_ball->x, position_ball->y, radius_ball->radius, GREEN);

        // Ball movement
        ball.set<goblock::component::Position>({
                position_ball->x + velocity_ball->x,
                position_ball->y + velocity_ball->y,
        });
        ball.set<goblock::component::Velocity>(
                {velocity_ball->x, velocity_ball->y + goblock::setup::GRAVITY});

        // Ball collision
        if (position_ball->y + radius_ball->radius >= GetScreenHeight() ||
                position_ball->y - radius_ball->radius <= 0) {
            ball.set<goblock::component::Velocity>(
                    {velocity_ball->x, velocity_ball->y * (-1)});
        }
        if (position_ball->x + radius_ball->radius >= GetScreenWidth() ||
                position_ball->x - radius_ball->radius <= 0) {
            ball.set<goblock::component::Velocity>(
                    {velocity_ball->x * (-1), velocity_ball->y});
        }

        // Render player
        const auto* position_player =
                player.get<goblock::component::Position>();
        const auto* size_player =
                player.get<goblock::component::SizeRectangle>();
        const auto* velocity_player =
                player.get<goblock::component::Velocity>();

        DrawRectangle(position_player->x, position_player->y,
                size_player->width, size_player->height, DARKPURPLE);

        // Player movement
        if (IsKeyDown(KEY_D)) {
            player.set<goblock::component::Position>(
                    {position_player->x + velocity_player->x,
                            position_player->y}); // move
            player.set<goblock::component::Velocity>(
                    {velocity_player->x + 1, velocity_player->y}); // accelerate
        } else if (IsKeyDown(KEY_A)) {
            player.set<goblock::component::Position>(
                    {position_player->x - velocity_player->x,
                            position_player->y}); // move
            player.set<goblock::component::Velocity>(
                    {velocity_player->x + 1, velocity_player->y}); // accelerate
        } else if (IsKeyReleased(KEY_A) || IsKeyReleased((KEY_D))) {
            player.set<goblock::component::Velocity>(
                    {velocity_player->x - 1, velocity_player->y}); // slowdown
        } else {
            player.set<goblock::component::Velocity>({0, 0}); // stop
        }

        EndDrawing();
    }

    // Cleanup
    goblock::game::GameScene::cleanup();

    return 0;
}
