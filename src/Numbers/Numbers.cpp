#include "Numbers.h"

numbers::Number::Number(game::Game* game, pictures::Pictures* pictures, int32_t id, int64_t value, common::Vec2<double> coordinate)
:m_pictures(pictures)
,m_id(id)
,m_value(value)
,m_coordinate(coordinate)
,m_velocity(0, 0)
,m_acceleration(0, 0)
{
    m_collision = new collision::Circle(game, m_coordinate.m_x, m_coordinate.m_y, RADIUS_OF_COLLISION);
    m_layerno = {my_main::Layer::NUMBER, m_id};
    m_color = vivid::hsl_t(0.7, 0.5, 0.5);
    // 数字の大きさに応じて色相を変える  change hue according to the largeness of number
    m_color.x -= 0.5 * (m_value / (STANDARD_DEVIATION * 1.5));
    m_color.x = fmod(m_color.x, 1.0);
    m_pictures->Add(m_layerno, "data/fonts/MPLUS1Code-SemiBold.ttf", std::to_string(m_value), numbers::PTSIZE, m_coordinate);
    m_pictures->SetPosition(m_layerno, 5);
    vivid::rgb_t rgb = vivid::rgb::fromHsl(m_color);
    m_pictures->SetRGBA(m_layerno, rgb.r * UINT8_MAX, rgb.g * UINT8_MAX, rgb.b * UINT8_MAX, UINT8_MAX);
    m_pictures->SetIsCameraTarget(m_layerno, true);
}

numbers::Number::~Number(){
    m_pictures->Delete(m_layerno);
    delete m_collision;
}

void numbers::Number::Move(){
    // 加速度から速度計算  Calculate velocity from acceleration
    m_velocity += m_acceleration;
    // 速度から座標計算  Calculate coordinate from velocity
    m_coordinate += m_velocity;
    // 当たり判定を移動  Move collision
    m_collision->center_display_x = m_coordinate.m_x;
    m_collision->center_display_y = m_coordinate.m_y;
}

void numbers::Number::Display(){
    m_pictures->SetXY(m_layerno, m_coordinate);
}

numbers::Numbers::Numbers(game::Game* game, pictures::Pictures* pictures, stage::Stage* stage, uint16_t simulation_accuracy)
:m_game(game)
,m_pictures(pictures)
,m_stage(stage)
,m_id(0)
,m_simulation_accuracy(simulation_accuracy)
{}

numbers::Numbers::~Numbers(){
    for(auto itr = m_numbers.begin(); itr != m_numbers.end(); itr++){
        delete itr->second;
    }
}

void numbers::Numbers::Add(){
    // ADD_FREQUENCYフレームに一度の頻度で  Once every ADD_FREQUENCY frames
    std::uniform_int_distribution<int32_t> dist1(0, ADD_FREQUENCY - 1);
    if(dist1(m_random) % ADD_FREQUENCY == 0){
        // 数字を追加  Add number
        std::normal_distribution<> dist2(0, STANDARD_DEVIATION);
        std::uniform_real_distribution<double> dist3(0, m_stage->GetWidth());
        std::uniform_real_distribution<double> dist4(0, m_stage->GetHeight());
        m_numbers[m_id] = new numbers::Number(m_game, m_pictures, m_id, int(std::abs(dist2(m_random))) + 1, {dist3(m_random), dist4(m_random)});
        m_id++;
    }
}

void numbers::Numbers::Delete(){
    // 各数字に対して  For each number
    for(auto itr = m_numbers.begin(); itr != m_numbers.end(); itr++){
        numbers::Number* number = itr->second;
        // DELETE_FREQUENCYフレームに一度の頻度で  Once every DELETE_FREQUENCY frames
        std::uniform_int_distribution<int32_t> dist1(0, DELETE_FREQUENCY - 1);
        if(dist1(m_random) % DELETE_FREQUENCY == 0){
            // 数字を削除  Delete number
            delete number;
            m_numbers.erase(itr);
        }
        // 数字がステージより100ピクセル以上外に出た場合  If the number is more than 100 pixels outside of the stage
        double x = number->GetCoordinate().m_x, y = number->GetCoordinate().m_y;
        if(x < -100 || x > m_stage->GetWidth() || y < -100 || y > m_stage->GetHeight()){
            // 数字を削除  Delete number
            delete number;
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
            // 万有引力の法則の定数を変えて分子をGCDの3乗にした形  Form of GCD squared molecules by changing the constant of the universal law of gravitation
            numbers::Number* number1 = itr1->second;
            numbers::Number* number2 = itr2->second;
            double dist = pow(sqrt(common::dist(number1->GetCoordinate().m_x, number1->GetCoordinate().m_y, number2->GetCoordinate().m_x, number2->GetCoordinate().m_y)), -POWERS_OF_DIST);
            common::Vec2<double> distxy = number2->GetCoordinate() - number1->GetCoordinate();
            int64_t gcd = std::gcd(number1->GetValue(), number2->GetValue());
            double attraction_mag = (CONSTANT_OF_ATTRACTION / std::pow(m_simulation_accuracy, 2)) * std::pow((gcd - 1), POWERS_OF_GCD) / dist;
            common::Vec2<double> attraction = {attraction_mag * (distxy.m_x / dist), attraction_mag * (distxy.m_y / dist)};
            number1->SetAcceleration(number1->GetAcceleration() + attraction);
        }
    }
}

void numbers::Numbers::MoveAll(){
    for(auto itr = m_numbers.begin(); itr != m_numbers.end(); itr++){
        numbers::Number* number = itr->second;
        number->Move();
    }
}

void numbers::Numbers::CalcCollisionAll(){
    // 衝突処理で最後に処理される数字が他の数字を押しのけることができないため、ランダムな順で処理する
    // The last number processed in the collision process cannot push the other numbers away, so they are processed in random order
    std::vector<int32_t> order(m_numbers.size());
    std::iota(order.begin(), order.end(), 0);
    std::shuffle(order.begin(), order.end(), m_random);
    for(int i = 0; i < int(m_numbers.size()); i++){
        auto itr1 = next(m_numbers.begin(), order[i]);
        numbers::Number* number1 = itr1->second;
        for(int j = i + 1; j < int(m_numbers.size()); j++){
            auto itr2 = next(m_numbers.begin(), order[j]);
            numbers::Number* number2 = itr2->second;
            // 2つの数字が衝突している場合  If two numbers are in collision
            double dir = collision::isInCollision(number1->GetCollision(), number2->GetCollision());
            if(dir != -1){
                // 数字を移動前の位置に戻す  Restore numbers to their pre-movement positions
                number2->SetCoordinate(number1->GetCoordinate() + common::Vec2<double>(RADIUS_OF_COLLISION * 2.01 * cos(dir + M_PI), RADIUS_OF_COLLISION * 2.01 * sin(dir + M_PI)));
                // 2つの数字の速度ベクトルを衝突方向に分解し、入れ替える  Resolution and swap the velocity vectors of two numbers in the direction of collision
                double resolution_vec_mag1, resolution_vec_mag2;
                common::Vec2<double> resolution_vec1, resolution_vec2;
                resolution_vec_mag1 = number1->GetVelocity().CalcMag() * std::cos(number1->GetVelocity().CalcDir() - dir);
                resolution_vec_mag2 = number2->GetVelocity().CalcMag() * std::cos(number2->GetVelocity().CalcDir() - (dir + M_PI));
                resolution_vec1.m_x = resolution_vec_mag1 * cos(dir);
                resolution_vec1.m_y = resolution_vec_mag1 * sin(dir);
                resolution_vec2.m_x = resolution_vec_mag2 * cos(dir + M_PI);
                resolution_vec2.m_y = resolution_vec_mag2 * sin(dir + M_PI);
                number1->SetVelocity((number1->GetVelocity() - resolution_vec1 + resolution_vec2) * COEFFICIENT_OF_RESTITUTION);
                number2->SetVelocity((number2->GetVelocity() - resolution_vec2 + resolution_vec1) * COEFFICIENT_OF_RESTITUTION);
            }
        }
    }
}

void numbers::Numbers::DisplayAll(){
    for(auto itr = m_numbers.begin(); itr != m_numbers.end(); itr++){
        itr->second->Display();
    }
}