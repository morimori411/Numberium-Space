#include "DrawCollision.h"

void collision::DrawCollision(collision::Rectangle* rectangle){
    SDL_Rect rect;
    rect.w = rectangle->right_display_x - rectangle->left_display_x;
    rect.h = rectangle->bottom_display_y - rectangle->top_display_y;
    rect.x = rectangle->left_display_x;
    rect.y = rectangle->top_display_y;
    SDL_RenderFillRect(rectangle->game->GetRenderer(), &rect);
}

void collision::DrawCollision(collision::Circle* circle){
    // x座標ごとに線を引いて円を描画
    SDL_Point points[int((circle->radius * 2 + 1) * 2)];
    // // 各x座標に関して
    for(int i = 0; i <= circle->radius * 2; i++){
        // x座標
        points[i * 2].x = circle->center_display_x + i - circle->radius;
        points[i * 2 + 1].x = circle->center_display_x + i - circle->radius;
        // y座標
        points[i * 2].y = circle->center_display_y + sqrt(pow(circle->radius, 2) - pow(i - circle->radius, 2));
        points[i * 2 + 1].y = circle->center_display_y - sqrt(pow(circle->radius, 2) - pow(i - circle->radius, 2));
    }
    SDL_RenderDrawLines(circle->game->GetRenderer(), points, (circle->radius * 2 + 1) * 2);
}