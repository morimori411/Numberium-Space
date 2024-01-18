#pragma once

#include <stdint.h>
#include "../Game.h"
#include "../Collision/Collision.h"
#include "../Collision/DrawCollision.h"

namespace stage{
    class Stage{
        private:
        game::Game* m_game;
        uint16_t m_height; // 高さ
        uint16_t m_width; // 幅
        collision::Rectangle* m_right; // 右の壁の当たり判定  Right wall collision detection
        collision::Rectangle* m_bottom; // 下の壁の当たり判定  Bottom wall collision detection
        collision::Rectangle* m_left; // 左の壁の当たり判定  Left wall collision detection
        collision::Rectangle* m_top; // 上の壁の当たり判定  Top wall collision detection

        public:
        Stage(game::Game* game, uint64_t height, uint64_t width);
        ~Stage();
        // 壁を表示
        void Display();
        // アクセサ
        uint64_t GetHeight() const {return m_height;}
        uint64_t GetWidth() const {return m_width;}
        collision::Rectangle* GetRight() const {return m_right;}
        collision::Rectangle* GetBottom() const {return m_bottom;}
        collision::Rectangle* GetLeft() const {return m_left;}
        collision::Rectangle* GetTop() const {return m_top;}
    };
}