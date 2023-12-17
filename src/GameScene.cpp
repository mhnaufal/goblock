#include "GameScene.h"

namespace goblock {
namespace game {

void GameScene::init(
        flecs::world& game_world, flecs::entity& ball, flecs::entity& player) {
    goblock::component::Position ball_position{goblock::setup::SCREEN_WIDTH / 2,
            goblock::setup::SCREEN_HEIGHT / 2};
    goblock::component::SizeCircle ball_size{15};
    goblock::component::Velocity ball_speed{0, 3};

    ball = goblock::system::create_object(
            game_world, "ball", ball_position, ball_size, ball_speed);

    goblock::component::SizeRectangle player_size{170, 30};
    goblock::component::Position player_position{
            goblock::setup::SCREEN_WIDTH / 2 - (player_size.width / 2),
            goblock::setup::SCREEN_HEIGHT - 50};

    goblock::component::Velocity player_velocity{2, 0};
    player = goblock::system::create_object(game_world, "player",
            player_position, player_size, player_velocity);
}

void GameScene::cleanup() {
    goblock::setup::game_screen = goblock::setup::GameScreen::GAME_OVER;
    CloseWindow();
    TraceLog(LOG_INFO, "Stopping GoBlock...");
    return;
}

} // namespace game
} // namespace goblock