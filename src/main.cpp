// goblock
#include "Component.h"
#include "GameScene.h"
#include "Setup.h"

Color GOBLOCK_GRAY{21, 27, 45};
Color GOBLOCK_WHITE{255, 251, 195, 255};
Color GOBLOCK_BLUE{131, 158, 238, 255};

int main()
{
    TraceLog(LOG_INFO, "Starting GoBlock...");

    // Initialize world, entity, object, etc
    flecs::world game_world{};
    flecs::entity ball{};
    flecs::entity player{};
    goblock::game::GameScene::init(game_world, ball, player);

    // Start the game process
    InitWindow(goblock::setup::SCREEN_WIDTH, goblock::setup::SCREEN_HEIGHT, goblock::setup::GAME_NAME.c_str());
    InitAudioDevice();

    Music music = LoadMusicStream("../assets/audio/battle.mp3");

    SetTargetFPS(60);

    goblock::setup::game_screen = goblock::setup::GameScreen::GAME;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GOBLOCK_GRAY);
        UpdateMusicStream(music);
        PlayMusicStream(music);

        // BALL
        const auto* position_ball = ball.get<goblock::component::Position>();
        const auto* radius_ball = ball.get<goblock::component::SizeCircle>();
        const auto* velocity_ball = ball.get<goblock::component::Velocity>();

        goblock::game::GameScene::render_ball(position_ball, radius_ball, GOBLOCK_WHITE);

        goblock::game::GameScene::movement_ball(ball, position_ball, velocity_ball);

        goblock::game::GameScene::collision_ball(ball, position_ball, radius_ball, velocity_ball);

        // PLAYER
        const auto* position_player = player.get<goblock::component::Position>();
        const auto* size_player = player.get<goblock::component::SizeRectangle>();
        const auto* velocity_player = player.get<goblock::component::Velocity>();

        goblock::game::GameScene::render_player(position_player, size_player, GOBLOCK_BLUE);

        goblock::game::GameScene::movement_player(player, position_player, velocity_player);

        goblock::game::GameScene::collision_player(player, position_player, size_player, velocity_player);

        // Ball and player collision
        if (CheckCollisionCircleRec(
                Vector2{position_ball->x, position_ball->y},
                radius_ball->radius,
                Rectangle{position_player->x, position_player->y, size_player->width, size_player->height})) {
            float degree = (position_ball->x <= (position_player->x + size_player->width / 2) &&
                            position_ball->x >= position_player->x) ?
                               (-1) :
                               (1);

            float rad = 15;
            auto prev = velocity_ball->x;
            ball.set<goblock::component::Velocity>({velocity_ball->x * degree, velocity_ball->y * (-1)});
            //            velocity_ball->x = prev;
        }

        EndDrawing();
    }

    // Cleanup
    UnloadMusicStream(music);
    goblock::game::GameScene::cleanup();

    return 0;
}
