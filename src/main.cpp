#include "main.h"

flecs::entity create_object(flecs::world& game_world, const std::string& name,
        const goblock::component::Position& pos,
        const goblock::component::SizeRectangle& size,
        const goblock::component::Velocity& vel) {
    auto object = game_world.entity(name.c_str());
    object.set<goblock::component::Position>({pos.x, pos.y});
    object.set<goblock::component::SizeRectangle>({size.width, size.height});
    object.set<goblock::component::Velocity>({vel.x, vel.y});
    return object;
}

flecs::entity create_object(flecs::world& game_world, const std::string& name,
        const goblock::component::Position& pos,
        const goblock::component::SizeCircle& size,
        const goblock::component::Velocity& vel) {
    auto object = game_world.entity(name.c_str());
    object.set<goblock::component::Position>({pos.x, pos.y});
    object.set<goblock::component::SizeCircle>({size.radius});
    object.set<goblock::component::Velocity>({vel.x, vel.y});
    return object;
}

int main() {
    TraceLog(LOG_INFO, "Starting GoBlock...");

    // Initialize game objects
    flecs::world game_world{};

    goblock::component::Position ball_position{goblock::setup::SCREEN_WIDTH / 2,
            goblock::setup::SCREEN_HEIGHT / 2};
    goblock::component::SizeCircle ball_size{15};
    goblock::component::Velocity ball_speed{0, 3};

    auto ball = create_object(
            game_world, "ball", ball_position, ball_size, ball_speed);

    goblock::component::SizeRectangle player_size{170, 30};
    goblock::component::Position player_position{
            goblock::setup::SCREEN_WIDTH / 2 - (player_size.width / 2),
            goblock::setup::SCREEN_HEIGHT - 50};
    goblock::component::Velocity player_velocity{2, 0};
    auto player = create_object(game_world, "player", player_position,
            player_size, player_velocity);

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

    goblock::setup::game_screen = goblock::setup::GameScreen::GAME_OVER;

    // Cleanup
    CloseWindow();

    TraceLog(LOG_INFO, "Stopping GoBlock...");

    return 0;
}
