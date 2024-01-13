#pragma once

#include <cstdint>

namespace common{
    struct Color{
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    int64_t dist(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
}