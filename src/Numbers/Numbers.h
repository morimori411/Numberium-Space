#pragma once

#include <random>
#include "../Pictures/Pictures.h"
#include "../Common/Vector.h"
#include "../Stage/Stage.h"

namespace numbers{
    const uint32_t ADD_FREQUENCY = 60; // 数字が追加される頻度[フレーム]  Frequency with which numbers are added[frame]
    const uint32_t DELETE_FREQUENCY = 30000; // 数字が削除される頻度[フレーム]  Frequency with which numbers are deleted[frame]
    const uint32_t STANDARD_DEVIATION = 50; // 標準偏差
    const double CONSTANT_OF_ATTRACTION = 0.003; // 万有引力定数
    const double POWERS_OF_DIST = -1.5; // 引力計算における距離の累乗数  Number of powers of distance in attraction force calculations
    const double POWERS_OF_GCD = 2.5; // 引力計算における最大公約数の累乗数  Number of powers of GCD in attraction force calculations
    const double RADIUS_OF_COLLISION = 16; // 数字の当たり判定の半径
    const double COEFFICIENT_OF_RESTITUTION = 0.9; // 反発係数
    const double DECELERATION = 0.999; // 毎フレームの減速量  Amount of deceleration per frame

    class Number{
        private:
        pictures::Pictures* m_pictures;
        collision::Circle* m_collision;
        int32_t m_id; // 各数字に個別に割り振る番号  Number to be assigned to each digit individually
        pictures::LayerAndNo m_layerno;
        int64_t m_value;
        common::Vec2 m_coordinate; // 座標
        common::Vec2 m_velocity; // 速度
        common::Vec2 m_acceleration; // 加速度

        public:
        Number(game::Game* game, pictures::Pictures* pictures, int32_t id, int64_t value, common::Vec2 coordinate);
        ~Number();
        void Move();
        void Display();
        // アクセサ  Accessor
        collision::Circle* GetCollision() const {return m_collision;}
        int64_t GetValue() const {return m_value;}
        common::Vec2 GetCoordinate() const {return m_coordinate;}
        common::Vec2 GetVelocity() const {return m_velocity;}
        common::Vec2 GetAcceleration() const {return m_acceleration;}
        void SetCoordinate(common::Vec2 coordinate){m_coordinate = coordinate;}
        void SetVelocity(common::Vec2 velocity){m_velocity = velocity;}
        void SetAcceleration(common::Vec2 acceleration){m_acceleration = acceleration;}
    };

    class Numbers{
        private:
        game::Game* m_game;
        std::random_device m_random;
        pictures::Pictures* m_pictures;
        stage::Stage* m_stage;
        int32_t m_id;
        std::map<int32_t, Number*> m_numbers;

        public:
        Numbers(game::Game* game, pictures::Pictures* pictures, stage::Stage* stage);
        ~Numbers();
        // 毎フレーム呼び出し 数字をランダムに追加  Every frame call. Add numbers randomly.
        void Add();
        // 毎フレーム呼び出し 数字をランダムに削除  Every frame call. Delete numbers randomly.
        void Delete();
        // 毎フレーム呼び出し 各数字間の引力を計算  Every frame call. Calculate the attraction between each number.
        void CalcAttraction();
        // 毎フレーム呼び出し 全数字の移動  Every frame call. Move all numbers
        void MoveAll();
        // 毎フレーム呼び出し 全数字の衝突の計算  Every frame call. Resolving all collision
        void CalcCollisionAll();
        // 毎フレーム呼び出し 全数字を画面に表示  Every frame call. Display all numbers on screen.
        void DisplayAll();
    };
}