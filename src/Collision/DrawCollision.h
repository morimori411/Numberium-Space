#pragma once

#include <SDL.h>
#include <cstdint>
#include <vector>
#include <math.h>

#include "../Game.h"
#include "Collision.h"

// 当たり判定関連
namespace collision{
    // 矩形の当たり判定の描画
    void DrawCollision(Rectangle* rectangle);
    // 円形の当たり判定の描画
    void DrawCollision(Circle* circle);
}