#pragma once

#include <stdint.h>
#include "../Collision/Collision.h"

namespace stage{
    class Stage{
        private:
        uint64_t height; // 高さ
        uint64_t width; // 幅
        collision::Rectangle right; // 右の壁の当たり判定  Right wall collision detection
        collision::Rectangle bottom; // 下の壁の当たり判定  Bottom wall collision detection
        collision::Rectangle left; // 左の壁の当たり判定  Left wall collision detection
        collision::Rectangle top; // 上の壁の当たり判定  Top wall collision detection

        public:
        Stage();
        ~Stage();
        // 壁を表示
        void Display();
    };
}