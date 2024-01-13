#pragma once

#include <cstdint>

namespace common{
    struct Vec2{
        double m_x;
        double m_y;

        // コンストラクタ
        Vec2();
        Vec2(double x, double y);
    };
}