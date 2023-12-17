#include "GameScene.h"

namespace goblock {
namespace game {

void GameScene::init(
        flecs::world& game_world, flecs::entity& ball, flecs::entity& player) {
    // initialize ball
    goblock::component::Position ball_position{
            static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2,
            static_cast<float>(goblock::setup::SCREEN_HEIGHT) / 6};
    goblock::component::SizeCircle ball_size{15};
    goblock::component::Velocity ball_speed{3, 3};

    ball = goblock::system::create_object(
            game_world, "ball", ball_position, ball_size, ball_speed);

    // initialize player
    goblock::component::SizeRectangle player_size{200, 30};
    goblock::component::Position player_position{
            static_cast<float>(goblock::setup::SCREEN_WIDTH) / 2 -
                    (player_size.width / 2),
            goblock::setup::SCREEN_HEIGHT - 100};

    goblock::component::Velocity player_velocity{4, 0};
    player = goblock::system::create_object(game_world, "player",
            player_position, player_size, player_velocity);
}

void GameScene::cleanup() {
    goblock::setup::game_screen = goblock::setup::GameScreen::GAME_OVER;
    CloseWindow();
    TraceLog(LOG_INFO, "Stopping GoBlock...");
}

} // namespace game
} // namespace goblock