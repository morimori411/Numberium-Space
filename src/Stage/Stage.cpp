#include "Stage.h"

stage::Stage::Stage(game::Game* game, uint64_t height, uint64_t width)
:m_game(game)
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

void stage::Stage::Display(){}