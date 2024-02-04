#pragma once

// goblock
#include <Component.h>
#include <Setup.h>
#include <System.h>

namespace goblock::game {

class GameScene {
public:
    static void
    init(flecs::world& game_world, flecs::entity& ball, flecs::entity& player, std::vector<flecs::entity>& blocks);

    /// BALL
    static void render_ball(
        const goblock::component::Position* position_ball,
        const goblock::component::SizeCircle* radius_ball,
        Color& color);

    static void movement_ball(
        flecs::entity& ball,
        const goblock::component::Position* position_ball,
        const goblock::component::Velocity* velocity_ball,
        const goblock::component::Direction* direction_ball);

    static void collision_ball(
        flecs::entity& ball,
        const goblock::component::Position* position_ball,
        const goblock::component::SizeCircle* radius_ball,
        const goblock::component::Velocity* velocity_ball,
        const goblock::component::Direction* direction_ball);

    static void ball_out(
        flecs::entity& ball,
        flecs::entity& player,
        const goblock::component::Position* position_ball,
        const goblock::component::SizeCircle* radius_ball,
        Sound& sound_lose,
        goblock::setup::GameScreen& game_screen);

    /// PLAYER
    static void render_player(
        const goblock::component::Position* position_player,
        const goblock::component::SizeRectangle* size_player,
        Color& color);

    static void movement_player(
        flecs::entity& player,
        const goblock::component::Position* position_player,
        const goblock::component::Velocity* velocity_player);

    static void collision_player(
        flecs::entity& player,
        const goblock::component::Position* position_player,
        const goblock::component::SizeRectangle* size_player);

    static void player_ball_collision(
        flecs::entity& ball,
        const goblock::component::Position* position_ball,
        const goblock::component::SizeCircle* radius_ball,
        [[maybe_unused]] const goblock::component::Velocity* velocity_ball,
        const goblock::component::Direction* direction_ball,
        const goblock::component::Position* position_player,
        const goblock::component::SizeRectangle* size_player,
        const Sound& sound_block);

    /// BLOCKS
    static std::vector<flecs::entity> create_blocks(
        flecs::world& game_world,
        goblock::component::Position& position_block,
        goblock::component::SizeRectangle& size_block,
        const int& block_count,
        const int start_position,
        const int space);

    static void render_blocks(
        flecs::entity& block,
        const goblock::component::Position* position_block,
        const goblock::component::SizeRectangle* size_block,
        Color& color);

    static void collision_block(
        flecs::entity& ball,
        flecs::entity& block,
        const goblock::component::Position* position_block,
        const goblock::component::SizeRectangle* size_block,
        const goblock::component::Position* position_ball,
        const goblock::component::SizeCircle* radius_ball,
        const goblock::component::Velocity* velocity_ball,
        const goblock::component::Direction* direction_ball,
        int& block_count);

    // Etc
    static void reset_game(flecs::entity& ball, flecs::entity& player);

    static void winning_check(Sound& sound_win, goblock::setup::GameScreen& game_screen, const int& block_count);

    static void debug_info(
        const goblock::component::Position* position_ball,
        const goblock::component::Velocity* velocity_ball,
        const int& block_count);

    static void cleanup(std::vector<Music>& musics, std::vector<Texture2D>& textures);

private:
};

} // namespace goblock::game
