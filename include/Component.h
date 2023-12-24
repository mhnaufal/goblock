#pragma once

// STL
#include <iostream>

namespace goblock {
/******************
 * Component
 ******************/
namespace component {

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
} // namespace component
} // namespace goblock