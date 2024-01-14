#include "Numbers.h"

numbers::Number::Number(pictures::Pictures* pictures, int32_t id, int64_t value, common::Vec2 coordinate)
:m_pictures(pictures)
,m_id(id)
,m_value(value)
,m_coordinate(coordinate)
,m_velocity(0, 0)
,m_acceleration(0, 0)
{
    m_layerno = {pictures::NUMBER, m_id};
    m_pictures->Add(m_layerno, "data/fonts/MPLUS1Code-Regular.ttf", std::to_string(m_value), 16, m_coordinate);
    m_pictures->SetPosition(m_layerno, 5);
}

numbers::Number::~Number(){
    m_pictures->Delete(m_layerno);
}

void numbers::Number::Move(){
    // 加速度から速度計算  Calculate velocity from acceleration
    m_velocity.m_x += m_acceleration.m_x;
    m_velocity.m_y += m_acceleration.m_y;
    // 速度から座標計算  Calculate coordinate from velocity
    m_coordinate.m_x += m_velocity.m_x;
    m_coordinate.m_y += m_velocity.m_y;
}

void numbers::Number::Display(){
    m_pictures->SetXY(m_layerno, m_coordinate);
}

numbers::Numbers::Numbers(pictures::Pictures* pictures, stage::Stage* stage)
:m_pictures(pictures)
,m_stage(stage)
,m_id(0)
{}

numbers::Numbers::~Numbers(){
    for(auto itr = m_numbers.begin(); itr != m_numbers.end(); itr++){
        delete itr->second;
    }
}

void numbers::Numbers::Add(){
    // 60フレームに一度の頻度で  Once every 60 frames
    std::uniform_int_distribution<int32_t> dist1(0, 59);
    if(dist1(m_random) % 60 == 0){
        // 数字を追加  Add number
        std::normal_distribution<> dist2(0, 100);
        std::uniform_real_distribution<double> dist3(0, m_stage->GetHeight());
        std::uniform_real_distribution<double> dist4(0, m_stage->GetWidth());
        m_numbers[m_id] = new numbers::Number(m_pictures, m_id, int(std::abs(dist2(m_random))), {dist3(m_random), dist4(m_random)});
        m_id++;
    }
}

void numbers::Numbers::Delete(){
    // 各数字に対して  For each number
    for(auto itr = m_numbers.begin(); itr != m_numbers.end(); itr++){
        // 10000フレームに一度の頻度で  Once every 10,000 frames
        std::uniform_int_distribution<int32_t> dist1(0, 9999);
        if(dist1(m_random) % 10000 == 0){
            // 数字を削除  Delete number
            delete itr->second;
            m_numbers.erase(itr);
        }
    }
}

void numbers::Numbers::CalcAttraction(){
    // 各数字間に対して  For each number between
    for(auto itr1 = m_numbers.begin(); itr1 != m_numbers.end(); itr1++){
        itr1->second->SetAcceleration({0, 0});
        for(auto itr2 = m_numbers.begin(); itr2 != m_numbers.end(); itr2++){
            if(itr1 == itr2) continue;
            // 万有引力の法則の定数を変えて分子をGCDの2乗にした形  Form of GCD squared molecules by changing the constant of the universal law of gravitation
            numbers::Number* number1 = itr1->second;
            numbers::Number* number2 = itr2->second;
            double dist = common::dist(number1->GetCoordinate().m_x, number1->GetCoordinate().m_y, number2->GetCoordinate().m_x, number2->GetCoordinate().m_y);
            common::Vec2 distxy = {number2->GetCoordinate().m_x - number1->GetCoordinate().m_x, number2->GetCoordinate().m_y - number1->GetCoordinate().m_y};
            int64_t gcd = std::gcd(number1->GetValue(), number2->GetValue());
            double attraction_mag = CONSTANT_OF_ATTRACTION * (gcd - 1) * (gcd - 1) / dist;
            common::Vec2 attraction = {attraction_mag * (distxy.m_x / dist), attraction_mag * (distxy.m_y / dist)};
            number1->SetAcceleration({number1->GetAcceleration().m_x + attraction.m_x, number1->GetAcceleration().m_y + attraction.m_y});
        }
    }
}

void numbers::Numbers::MoveAll(){
    for(auto itr = m_numbers.begin(); itr != m_numbers.end(); itr++){
        itr->second->Move();
    }
}

void numbers::Numbers::DisplayAll(){
    for(auto itr = m_numbers.begin(); itr != m_numbers.end(); itr++){
        itr->second->Display();
    }
}