#pragma once

#include <stdint.h>
#include "../Game.h"
#include "../Collision/Collision.h"
#include "../Collision/DrawCollision.h"

namespace stage{
    class Stage{
        private:
        game::Game* m_game;
        uint64_t m_height; // 高さ
        uint64_t m_width; // 幅
        collision::Rectangle m_right; // 右の壁の当たり判定  Right wall collision detection
        collision::Rectangle m_bottom; // 下の壁の当たり判定  Bottom wall collision detection
        collision::Rectangle m_left; // 左の壁の当たり判定  Left wall collision detection
        collision::Rectangle m_top; // 上の壁の当たり判定  Top wall collision detection

        public:
        Stage(game::Game* game, uint64_t height, uint64_t width);
        ~Stage();
        // 壁を表示
        void Display();
    };
}