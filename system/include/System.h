#pragma once

// goblock
#include "Component.h"

// Third-party
#include <flecs.h>
#include <raylib.h>

// STL
#include <cassert>
#include <cstring>
#include <iostream>

/******************
 * System
 ******************/
namespace goblock::system {

flecs::entity create_object(
    flecs::world& game_world,
    const std::string& name,
    const component::Position& pos,
    const component::SizeRectangle& size,
    const component::Velocity& vel);

flecs::entity create_object(
    flecs::world& game_world,
    const std::string& name,
    const component::Position& pos,
    const component::SizeRectangle& size,
    const component::Velocity& vel,
    const component::Destroyed& is_destroyed);

flecs::entity create_object(
    flecs::world& game_world,
    const std::string& name,
    const component::Position& pos,
    const component::SizeCircle& size,
    const component::Velocity& vel,
    const component::Direction& dir);

} // namespace goblock::system
