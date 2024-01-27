#pragma once

// STL
#include <iostream>

/******************
 * Component
 ******************/
namespace goblock::component {

struct Position {
public:
    float x{};
    float y{};
};

struct Velocity {
public:
    float x{};
    float y{};
};

struct Direction {
public:
    float x{};
    float y{};
};

struct SizeRectangle {
public:
    float width{};
    float height{};
};

struct SizeCircle {
public:
    float radius{};
};

struct Destroyed {
public:
    bool is_destroyed{false};
};

struct DebugInfo {
public:
    Position ball_position;
    Velocity ball_velocity;
    Position player_position;
    Velocity player_velocity;
};

} // namespace goblock::component
