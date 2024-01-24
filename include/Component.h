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
} // namespace goblock::component
