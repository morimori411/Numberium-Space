#include "Stage.h"

stage::Stage::Stage(game::Game* game, pictures::Pictures* pictures, uint64_t height, uint64_t width)
:m_game(game)
,m_pictures(pictures)
,m_height(height)
,m_width(width)
{
    m_right = new collision::Rectangle(m_game, width + 100, height + 100, width, -100);
    m_bottom = new collision::Rectangle(m_game, width + 100, height + 100, -100, height);
    m_left = new collision::Rectangle(m_game, 0, height + 100, -100, -100);
    m_top = new collision::Rectangle(m_game, width + 100, 0, -100, -100);
}

stage::Stage::~Stage(){
    delete m_right;
    delete m_bottom;
    delete m_left;
    delete m_top;
}

void stage::Stage::Display(){
    // 背景  Background
    m_pictures->Add({my_main::Layer::BACK, 0}, "back", {0, 0});
    common::Vec2<float> back_jpg_size = m_pictures->GetTextures()->GetTextureSize("back");
    m_pictures->SetScale({my_main::Layer::BACK, 0}, common::Vec2<float>(m_game->GetWindowSize().x / back_jpg_size.x, m_game->GetWindowSize().y / back_jpg_size.y));
    //線 line
    common::Vec2<int16_t> center_of_stage(m_width / 2, m_height / 2);
    for(int y = center_of_stage.y - m_height; y <= center_of_stage.x + m_height; y += DIST_BETWEEN_LINE){
        pictures::LayerNo layerno = {my_main::Layer::HOR_LINE, y};
        m_pictures->Add(layerno, "ver", {0, static_cast<double>(y)});
        m_pictures->SetPosition(layerno, 5);
        m_pictures->SetScale(layerno, {m_width * 2.0, 1.0});
        m_pictures->SetIsCameraTarget(layerno, true);
    }
    for(int x = center_of_stage.x - m_width; x <= center_of_stage.x + m_width; x += DIST_BETWEEN_LINE){
        pictures::LayerNo layerno = {my_main::Layer::VER_LINE, x};
        m_pictures->Add(layerno, "hor", {static_cast<double>(x), 0});
        m_pictures->SetPosition(layerno, 5);
        m_pictures->SetScale(layerno, {1.0, m_height * 2.0});
        m_pictures->SetIsCameraTarget(layerno, true);
    }
}