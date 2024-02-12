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
    m_pictures->Add({pictures::BACK, 0}, "data/images/back.jpg", {0, 0});
    //線 line
    common::Vec2 center_of_stage(m_width / 2, m_height / 2);
    for(int y = center_of_stage.m_y - m_height; y <= center_of_stage.m_x + m_height; y += DIST_BETWEEN_LINE){
        pictures::LayerAndNo layerno = {pictures::VER_LINE, y};
        m_pictures->Add(layerno, "data/images/ver_line.png", {0, static_cast<double>(y)});
        m_pictures->SetPosition(layerno, 5);
        m_pictures->SetScale(layerno, {m_width * 2.0, 1.0});
        m_pictures->SetIsCameraTarget(layerno, true);
    }
    for(int x = center_of_stage.m_x - m_width; x <= center_of_stage.m_x + m_width; x += DIST_BETWEEN_LINE){
        pictures::LayerAndNo layerno = {pictures::HOR_LINE, x};
        m_pictures->Add(layerno, "data/images/hor_line.png", {static_cast<double>(x), 0});
        m_pictures->SetPosition(layerno, 5);
        m_pictures->SetScale(layerno, {1.0, m_height * 2.0});
        m_pictures->SetIsCameraTarget(layerno, true);
    }
}