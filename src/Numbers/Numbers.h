#pragma once

#include <vector>
#include "../Pictures/Pictures.h"
#include "../Common/Vector.h"

namespace numbers{
        class Number{
        private:
        pictures::Pictures* m_pictures;
        int32_t m_id; // 各数字に個別に割り振る番号  Number to be assigned to each digit individually
        pictures::LayerAndNo m_layerno;
        int64_t m_value;
        common::Vec2 m_coordinate; // 座標
        common::Vec2 m_velocity; // 速度
        common::Vec2 m_acceleration; // 加速度

        public:
        Number(pictures::Pictures* pictures, int32_t id, int64_t value, common::Vec2 coordinate);
        ~Number();
        void Move();
        void Display();
    };

    class Numbers{
        private:
        pictures::Pictures* m_pictures;
        std::vector<Number*> m_numbers;

        public:
        Numbers();
        ~Numbers();
        // 毎フレーム呼び出し 数字をランダムに追加  Every frame call. Add numbers randomly.
        void Add(pictures::Pictures* pictures, uint64_t value, common::Vec2 coordinate);
        // 毎フレーム呼び出し 数字をランダムに削除  Every frame call. Delete numbers randomly.
        void Delete();
        // 毎フレーム呼び出し 各数字間の引力を計算  Every frame call. Calculate the attraction between each number.
        void CalcAttraction();
        // 毎フレーム呼び出し 全数字の移動と重なりの解決  Every frame call. Resolving Movement and Overlap of All Numbers.
        void MoveAll();
        // 毎フレーム呼び出し 全数字を画面に表示  Every frame call. Display all numbers on screen.
        void DisplayAll();
    };
}