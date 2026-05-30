#include "GameScene.h"

int goblock::setup::SCORE{0};
int goblock::setup::LIVE{3};

namespace goblock::game {

void GameScene::init(
    flecs::world& game_world, flecs::entity& ball, flecs::entity& player, std::vector<flecs::entity>& blocks)
{
    // initialize ball
    goblock::component::Position ball_position{
        static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2, static_cast<float>(goblock::setup::SCREEN_HEIGHT) / 6};
    goblock::component::SizeCircle ball_size{14};
    goblock::component::Velocity ball_speed{setup::BALL_SPEED, setup::BALL_SPEED};
    goblock::component::Direction ball_direction{1, 1};

    ball = goblock::system::create_object(game_world, "ball", ball_position, ball_size, ball_speed, ball_direction);

    // initialize player
    goblock::component::SizeRectangle player_size{250, 30};
    goblock::component::Position player_position{
        static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2 - (player_size.width / 2),
        goblock::setup::SCREEN_HEIGHT - 80};

    goblock::component::Velocity player_velocity{6, 0};
    player = goblock::system::create_object(game_world, "player", player_position, player_size, player_velocity);

    // initialize blocks
    assert(!blocks.empty());

    goblock::component::Destroyed is_destroyed{false};
    goblock::component::SizeRectangle block_size{};
    goblock::component::Position block_position{};

    switch (goblock::setup::level_screen) {
    case goblock::setup::LevelScreen::LEVEL_1:
        for (int i = 0; i < blocks.size(); ++i) {
            block_size.width = 80;
            block_size.height = 25;
            block_position.x = static_cast<float>(150 + (i * 110));
            block_position.y = 200;
            auto block = goblock::system::create_object(
                game_world, &"block" [i], block_position, block_size, { 0, 0 }, is_destroyed);
            blocks[i] = block;
        }
        break;
    case goblock::setup::LevelScreen::LEVEL_2:
        for (int i = 0; i < blocks.size(); ++i) {
            block_size.width = 70;
            block_size.height = 35;
            block_position.y = 80;
            if (i >= 10 && i < 20) {
                block_position.x = static_cast<float>(110 + ((i - 10) * 110));
                block_position.y = 150;
            }
            else if (i >= 20) {
                block_position.x = static_cast<float>(110 + ((i - 20) * 110));
                block_position.y = 220;
            }
            else {
                block_position.x = static_cast<float>(110 + (i * 110));
            }
            auto block = goblock::system::create_object(
                game_world, &"block"[i], block_position, block_size, player_velocity, is_destroyed);
            blocks[i] = block;
        }
        break;
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
    const goblock::component::Velocity* velocity_ball,
    const goblock::component::Direction* direction_ball)
{
    ball.set<goblock::component::Position>({position_ball->x + velocity_ball->x, position_ball->y + velocity_ball->y});
    ball.set<goblock::component::Direction>({direction_ball->x, direction_ball->y});
}

void GameScene::collision_ball(
    flecs::entity& ball,
    const goblock::component::Position* position_ball,
    const goblock::component::SizeCircle* radius_ball,
    const goblock::component::Velocity* velocity_ball,
    const goblock::component::Direction* direction_ball)
{
    // Ball & wall collision
    if (position_ball->x - radius_ball->radius <= 0 ||
        position_ball->x + radius_ball->radius >= (float)GetScreenWidth()) {
        ball.set<goblock::component::Velocity>({velocity_ball->x * -1, velocity_ball->y});
        ball.set<goblock::component::Direction>({direction_ball->x * -1, direction_ball->y});
        auto ball_velocity = ball.get<goblock::component::Velocity>();
    }

    if (position_ball->y - radius_ball->radius <= 0) {
        ball.set<goblock::component::Velocity>({velocity_ball->x, velocity_ball->y * (-1)});
        ball.set<goblock::component::Direction>({direction_ball->x, 1});
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
std::vector<flecs::entity> GameScene::create_blocks(
    flecs::world& game_world,
    goblock::component::Position& position_block,
    goblock::component::SizeRectangle& size_block,
    const int& block_count,
    const int start_position,
    const int space)
{
    std::vector<flecs::entity> blocks{(unsigned)block_count};
    component::Destroyed is_destroyed{false};

    for (int i = 0; i < block_count; ++i) {
        if (i >= 8 && i <= 16) {
            position_block.y = 275;
            position_block.x = static_cast<float>(start_position + ((i - 8.0) * space));
        }
        else {
            position_block.x = static_cast<float>(start_position + (i * space));
        }

        auto block = goblock::system::create_object(
            game_world, &"block" [i], position_block, size_block, { 0, 0 }, is_destroyed);
        blocks[i] = block;
    }

    return blocks;
}

void GameScene::render_blocks(
    flecs::entity& block,
    const goblock::component::Position* position_block,
    const goblock::component::SizeRectangle* size_block,
    Color& color)
{
    const auto* is_destroyed = block.try_get<component::Destroyed>();
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
    const goblock::component::Velocity* velocity_ball,
    const goblock::component::Direction* direction_ball,
    int& block_count)
{
    const auto* is_destroyed = block.try_get<component::Destroyed>();
    if (is_destroyed->is_destroyed) {
        return;
    }

    // TODO: collision from top and bottom are different
    if (CheckCollisionCircleRec(
            Vector2{position_ball->x, position_ball->y},
            radius_ball->radius,
            Rectangle{position_block->x, position_block->y, size_block->width, size_block->height})) {
        ball.set<goblock::component::Velocity>({velocity_ball->x, velocity_ball->y * -1});
        ball.set<goblock::component::Direction>({direction_ball->x * 1, direction_ball->y * -1});
        block.set<goblock::component::Destroyed>({true});

        block_count -= 1;
        goblock::setup::SCORE += 1;
    }
}

void GameScene::player_ball_collision(
    flecs::entity& ball,
    const goblock::component::Position* position_ball,
    const goblock::component::SizeCircle* radius_ball,
    [[maybe_unused]] const goblock::component::Velocity* velocity_ball,
    const goblock::component::Direction* direction_ball,
    const goblock::component::Position* position_player,
    const goblock::component::SizeRectangle* size_player,
    const Sound& sound_block)
{
    if (CheckCollisionCircleRec(
            Vector2{position_ball->x, position_ball->y},
            radius_ball->radius,
            Rectangle{position_player->x, position_player->y, size_player->width, size_player->height})) {
        PlaySound(sound_block);

        auto player_center = position_player->x + size_player->width / 2;
        auto distance_to_center = position_ball->x - player_center;
        auto percent_width = distance_to_center / size_player->width;
        auto angle = percent_width * 90;
        auto angle_radian = angle * DEG2RAD;
        auto new_x_velocity = sin(angle_radian) * setup::BALL_SPEED * 1.5f;
        auto new_y_velocity = cos(angle_radian) * setup::BALL_SPEED * -1.5f;

        ball.set<goblock::component::Velocity>({new_x_velocity, new_y_velocity});
        ball.set<goblock::component::Direction>({direction_ball->x, -1});
    }
}

void GameScene::ball_out(
    flecs::entity& ball,
    flecs::entity& player,
    const goblock::component::Position* position_ball,
    const goblock::component::SizeCircle* radius_ball,
    Sound& sound_lose,
    goblock::setup::GameScreen& game_screen)
{
    if (position_ball->y + radius_ball->radius >= (float)GetScreenHeight()) {
        PlaySound(sound_lose);
        goblock::setup::LIVE--;
        if (goblock::setup::LIVE <= 0) {
            game_screen = goblock::setup::GameScreen::GAME_OVER;
        }
        else {
            reset_game(ball, player);
        }
    }
}

void GameScene::reset_game(flecs::entity& ball, flecs::entity& player)
{
    ball.set<goblock::component::Position>(
        {static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2, static_cast<float>(goblock::setup::SCREEN_HEIGHT) / 6});
    player.set<goblock::component::Position>(
        {static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2 -
             (player.try_get<goblock::component::SizeRectangle>()->width / 2),
         goblock::setup::SCREEN_HEIGHT - 80});
}

void GameScene::winning_check(Sound& sound_win, goblock::setup::GameScreen& game_screen, const int& block_count)
{
    if (block_count <= 0) {
        PlaySound(sound_win);
        game_screen = goblock::setup::GameScreen::GAME_VICTORY;
        switch (goblock::setup::level_screen) {
        case setup::LevelScreen::LEVEL_1:
            goblock::setup::level_screen = setup::LevelScreen::LEVEL_2;
            break;
        case setup::LevelScreen::LEVEL_2:
            // TODO: change to level 3
            goblock::setup::level_screen = setup::LevelScreen::LEVEL_1;
            break;
        }
    }
}

void GameScene::debug_info(
    const goblock::component::Position* position_ball,
    const goblock::component::Velocity* velocity_ball,
    const int& block_count)
{
    DrawText(TextFormat("Ball x: %2.2f", position_ball->x / 10), 0, 0, 20, WHITE);
    DrawText(TextFormat("Ball y: %2.2f", position_ball->y / 10), 0, 25, 20, WHITE);

    DrawText(TextFormat("Ball Vx: %2.2f", velocity_ball->x / 10), 0, 50, 20, WHITE);
    DrawText(TextFormat("Ball Vy: %2.2f", velocity_ball->y / 10), 0, 75, 20, WHITE);

    DrawText(TextFormat("Block: %d", block_count), 0, 100, 20, WHITE);

    DrawText(TextFormat("Level: %d", goblock::setup::level_screen), 0, 125, 20, WHITE);
}

void GameScene::cleanup(std::vector<Music>& musics, std::vector<Texture2D>& textures)
{
    goblock::setup::game_screen = goblock::setup::GameScreen::GAME_END;

    for (const auto& texture : textures) { UnloadTexture(texture); }
    for (const auto& music : musics) { UnloadMusicStream(music); }
    CloseAudioDevice();
    CloseWindow();
    TraceLog(LOG_INFO, "Stopping GoBlock...");
}

} // namespace goblock::game
