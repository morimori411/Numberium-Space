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

numbers::Numbers::Numbers(){}

numbers::Numbers::~Numbers(){}

void numbers::Numbers::Add(pictures::Pictures* pictures, uint64_t value, common::Vec2 coordinate){}

void numbers::Numbers::Delete(){}

void numbers::Numbers::CalcAttraction(){}

void numbers::Numbers::MoveAll(){}

void numbers::Numbers::DisplayAll(){}