#include "GameScene.h"

namespace goblock::game {

void GameScene::init(flecs::world& game_world, flecs::entity& ball, flecs::entity& player)
{
    // initialize ball
    goblock::component::Position ball_position{
        static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2, static_cast<float>(goblock::setup::SCREEN_HEIGHT) / 6};
    goblock::component::SizeCircle ball_size{15};
    goblock::component::Velocity ball_speed{2, 2};

    ball = goblock::system::create_object(game_world, "ball", ball_position, ball_size, ball_speed);

    // initialize player
    goblock::component::SizeRectangle player_size{1000, 30};
    goblock::component::Position player_position{
        static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2 - (player_size.width / 2),
        goblock::setup::SCREEN_HEIGHT - 100};

    goblock::component::Velocity player_velocity{6, 0};
    player = goblock::system::create_object(game_world, "player", player_position, player_size, player_velocity);
}

/// BALL
void GameScene::render_ball(
    const goblock::component::Position* position_ball, const goblock::component::SizeCircle* radius_ball, Color& color)
{
    DrawCircle(position_ball->x, position_ball->y, radius_ball->radius, color);
}

void GameScene::movement_ball(
    flecs::entity& ball,
    const goblock::component::Position* position_ball,
    const goblock::component::Velocity* velocity_ball)
{
    // Ball movement
    ball.set<goblock::component::Position>({
        position_ball->x + velocity_ball->x,
        position_ball->y + velocity_ball->y,
    });
}

void GameScene::collision_ball(
    flecs::entity& ball,
    const goblock::component::Position* position_ball,
    const goblock::component::SizeCircle* radius_ball,
    const goblock::component::Velocity* velocity_ball)
{
    // Ball & wall collision
    int rand_x_direction = GetRandomValue(-1, 1) * (360 / 45);
    if (position_ball->y - radius_ball->radius <= 0) {
        ball.set<goblock::component::Velocity>({velocity_ball->x + rand_x_direction, velocity_ball->y * (-1)});
    }
    if (position_ball->x + radius_ball->radius >= GetScreenWidth() || position_ball->x - radius_ball->radius <= 0) {
        ball.set<goblock::component::Velocity>({velocity_ball->x * (-1), velocity_ball->y * -1});
    }
    else {
        ball.set<goblock::component::Velocity>({velocity_ball->x, velocity_ball->y + goblock::setup::GRAVITY});
    }
}

/// PLAYER
void GameScene::render_player(
    const goblock::component::Position* position_player,
    const goblock::component::SizeRectangle* size_player,
    Color& color)
{
    DrawRectangleRounded(
        Rectangle{position_player->x, position_player->y, size_player->width, size_player->height}, 3, 3, color);
}

void GameScene::movement_player(
    flecs::entity& player,
    const goblock::component::Position* position_player,
    const goblock::component::Velocity* velocity_player)
{
    // Player movement
    if (IsKeyDown(KEY_D)) {
        player.set<goblock::component::Position>({position_player->x + velocity_player->x, position_player->y}); // move
        player.set<goblock::component::Velocity>({velocity_player->x + 1, velocity_player->y}); // accelerate
    }
    else if (IsKeyDown(KEY_A)) {
        player.set<goblock::component::Position>({position_player->x - velocity_player->x, position_player->y}); // move
        player.set<goblock::component::Velocity>({velocity_player->x + 1, velocity_player->y}); // accelerate
    }
    else if (IsKeyReleased(KEY_A) || IsKeyReleased((KEY_D))) {
        player.set<goblock::component::Velocity>({velocity_player->x - 1, velocity_player->y}); // slowdown
    }
    else {
        player.set<goblock::component::Velocity>({0, 0}); // stop
    }
}
void GameScene::collision_player(
    flecs::entity& player,
    const goblock::component::Position* position_player,
    const goblock::component::SizeRectangle* size_player,
    const goblock::component::Velocity* velocity_player)
{
    // Player and wall collision
    if (position_player->x <= 0) {
        player.set<goblock::component::Position>({0, position_player->y});
    }
    else if (position_player->x + size_player->width >= GetScreenWidth()) {
        player.set<goblock::component::Position>(
            {static_cast<float>(GetScreenWidth()) - size_player->width, position_player->y});
    }
}

void GameScene::cleanup()
{
    goblock::setup::game_screen = goblock::setup::GameScreen::GAME_OVER;
    CloseAudioDevice();
    CloseWindow();
    TraceLog(LOG_INFO, "Stopping GoBlock...");
}

} // namespace goblock::game
