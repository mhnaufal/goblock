#include "GameScene.h"

int goblock::setup::BLOCK_COUNT{8};

namespace goblock::game {

void GameScene::init(
    flecs::world& game_world, flecs::entity& ball, flecs::entity& player, std::vector<flecs::entity>& blocks)
{
    // initialize ball
    goblock::component::Position ball_position{
        static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2, static_cast<float>(goblock::setup::SCREEN_HEIGHT) / 6};
    goblock::component::SizeCircle ball_size{12};
    goblock::component::Velocity ball_speed{0.2, 0.2};

    ball = goblock::system::create_object(game_world, "ball", ball_position, ball_size, ball_speed);

    // initialize player
    goblock::component::SizeRectangle player_size{400, 30};
    goblock::component::Position player_position{
        static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2 - (player_size.width / 2),
        goblock::setup::SCREEN_HEIGHT - 80};

    goblock::component::Velocity player_velocity{6, 0};
    player = goblock::system::create_object(game_world, "player", player_position, player_size, player_velocity);

    // initialize blocks
    component::Destroyed is_destroyed{};
    is_destroyed.is_destroyed = false;
    for (int i = 0; i < blocks.size(); ++i) {
        goblock::component::SizeRectangle block_size{70, 30};
        goblock::component::Position block_position{
            static_cast<float>(110 + (i * 100)),
            //            static_cast<float>(50 + (i * 20)),
            200,
        };

        auto block = goblock::system::create_object(
            game_world, &"block"[i], block_position, block_size, player_velocity, is_destroyed);
        blocks[i] = block;
    }
}

/// BALL
void GameScene::render_ball(
    const goblock::component::Position* position_ball, const goblock::component::SizeCircle* radius_ball, Color& color)
{
    DrawCircle((int)position_ball->x, (int)position_ball->y, radius_ball->radius, color);
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
    int rand_x_direction = GetRandomValue(-1, 1) * (360 / 150);
    if (position_ball->y - radius_ball->radius <= 0) {
        ball.set<goblock::component::Velocity>(
            {velocity_ball->x * (float)rand_x_direction, (velocity_ball->y / (float)1.4) * (-1)});
        ball.set<goblock::component::Position>({position_ball->x, position_ball->y + velocity_ball->y});
    }
    if (position_ball->x + radius_ball->radius >= (float)GetScreenWidth() ||
        position_ball->x - radius_ball->radius <= 0) {
        ball.set<goblock::component::Velocity>({velocity_ball->x * (-1), velocity_ball->y * (-1) * (float)1.2});
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
    const goblock::component::SizeRectangle* size_player)
{
    // Player and wall collision
    if (position_player->x <= 0 - 150) {
        player.set<goblock::component::Position>({0 - 150, position_player->y});
    }
    if (position_player->x + size_player->width >= (float)GetScreenWidth() + 150) {
        player.set<goblock::component::Position>(
            {static_cast<float>(GetScreenWidth()) - size_player->width + 150, position_player->y});
    }
}

/// BLOCKS
void GameScene::render_blocks(
    flecs::entity& block,
    const goblock::component::Position* position_block,
    const goblock::component::SizeRectangle* size_block,
    Color& color)
{
    const auto* is_destroyed = block.get<component::Destroyed>();
    if (!is_destroyed->is_destroyed) {
        DrawRectangle(
            (int)position_block->x, (int)position_block->y, (int)size_block->width, (int)size_block->height, color);
    }
}

void GameScene::collision_block(
    flecs::entity& ball,
    flecs::entity& block,
    const goblock::component::Position* position_block,
    const goblock::component::SizeRectangle* size_block,
    const goblock::component::Position* position_ball,
    const goblock::component::SizeCircle* radius_ball,
    const goblock::component::Velocity* velocity_ball)
{
    const auto* is_destroyed = block.get<component::Destroyed>();
    if (is_destroyed->is_destroyed) {
        return;
    }

    if (CheckCollisionCircleRec(
            Vector2{position_ball->x, position_ball->y},
            radius_ball->radius,
            Rectangle{position_block->x, position_block->y, size_block->width, size_block->height})) {
        ball.set<goblock::component::Velocity>({velocity_ball->x * (float)1.2, (velocity_ball->y / (float)1.3) * (-1)});
        block.set<goblock::component::Destroyed>({true});
        goblock::setup::BLOCK_COUNT -= 1;
    }
}

void GameScene::player_ball_collision(
    flecs::entity& ball,
    const goblock::component::Position* position_ball,
    const goblock::component::SizeCircle* radius_ball,
    const goblock::component::Velocity* velocity_ball,
    const goblock::component::Position* position_player,
    const goblock::component::SizeRectangle* size_player,
    const Sound& sound_block)
{
    if (CheckCollisionCircleRec(
            Vector2{position_ball->x, position_ball->y},
            radius_ball->radius,
            Rectangle{position_player->x, position_player->y, size_player->width, size_player->height})) {
        float degree = (position_ball->x <= (position_player->x + size_player->width / 2) &&
                        position_ball->x >= position_player->x) ?
                           (-3.5) :
                           (3.5);

        PlaySound(sound_block);

        ball.set<goblock::component::Velocity>({velocity_ball->x + degree, (velocity_ball->y) * (-1)});
    }
}

void GameScene::cleanup(Music& music)
{
    goblock::setup::game_screen = goblock::setup::GameScreen::GAME_END;
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
    TraceLog(LOG_INFO, "Stopping GoBlock...");
}

} // namespace goblock::game
