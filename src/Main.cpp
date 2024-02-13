#include "Main.h"

int main(int argc, char* argv[]){
    game::Game* game = new game::Game(
        my_main::GAME_TITLE,
        my_main::FLAGS_SDL_INIT,
        my_main::FLAGS_IMG_INIT,
        my_main::WINDOW_FLAGS,
        my_main::RENDERER_FLAGS,
        my_main::FPS
    );
    game->Initialize();
    pictures::Textures* textures = new pictures::Textures(game);
    pictures::Fonts* fonts = new pictures::Fonts;
    pictures::TextTextures* text_textures = new pictures::TextTextures(game, fonts);
    pictures::Camera* camera = new pictures::Camera;
    pictures::Pictures* pictures = new pictures::Pictures(game, textures, text_textures, camera);
    stage::Stage* stage = new stage::Stage(game, pictures, 5000, 5000);
    numbers::Numbers* numbers = new numbers::Numbers(game, pictures, stage, my_main::SIMULATION_ACCURACY);

    // メインループ  Main loop
    SDL_Event event;
    fonts->LoadFont("data/fonts/MPLUS1Code-SemiBold.ttf");
    textures->LoadFile("data/images/back.jpg");
    textures->LoadFile("data/images/hor_line.png");
    textures->LoadFile("data/images/ver_line.png");
    stage->Display();
    bool current_left_button, old_left_button;// 左クリックの状態  Left-click status
    common::Vec2<int32_t> mouse_xy; // マウスの座標  Mouse coordinates
    common::Vec2<double> mouse_abs_xy; // マウスの絶対座標  Mouse absolute coordinates 
    common::Vec2<double> drag_start_mouse_xy; // ドラッグ開始時のマウスの座標  Mouse coordinates of the start of the drag
    common::Vec2<double> drag_start_camera_xy; // ドラッグ開始時のカメラの座標  Camera coordinates at the start of the drag
    while(game->GetIsRunning()){
        current_left_button = false;
        // SDL_Event
        while(SDL_PollEvent(&event)){
            // ズーム  Zoom
            if(event.type == SDL_MOUSEWHEEL){
                SDL_GetMouseState(&mouse_xy.m_x, &mouse_xy.m_y);
                mouse_abs_xy = camera->GetXY() + static_cast<common::Vec2<double>>(mouse_xy) * (1 / camera->GetZoom());
                camera->SetZoom(std::max(my_main::MAX_CAMERA_ZOOM, camera->GetZoom() + event.wheel.y * my_main::CAMERA_ZOOM_STEP));
                camera->SetXY(mouse_abs_xy - static_cast<common::Vec2<double>>(mouse_xy) * (1 / camera->GetZoom()));
            }
            // ゲーム終了  End of game
            if(event.type == SDL_QUIT) game->SetIsRunning(false);
        }
        // マウスでのカメラ操作  Camera operation with mouse
        // 新しく左クリックされたとき  When newly left-clicked
        current_left_button = SDL_GetMouseState(&mouse_xy.m_x, &mouse_xy.m_y) & SDL_BUTTON(1);
        if(current_left_button && !old_left_button){
            // ドラッグ開始
            drag_start_mouse_xy = mouse_xy;
            drag_start_camera_xy = camera->GetXY();
        }
        // 左クリックされているとき  When the left mouse button is clicked
        if(current_left_button){
            // カメラを移動させる
            camera->SetXY(drag_start_camera_xy - (static_cast<common::Vec2<double>>(mouse_xy) - drag_start_mouse_xy) * (1 / camera->GetZoom()));
        }
        // カメラをステージの範囲内に収める  Keep camera within stage range
        if(camera->GetXY().m_x < 0){
            camera->SetXY({0, camera->GetXY().m_y});
        }
        if(camera->GetXY().m_y < 0){
            camera->SetXY({camera->GetXY().m_x, 0});
        }
        if(camera->GetXY().m_x + game->GetWindowSize().m_x * (1 / camera->GetZoom()) > stage->GetWidth()){
            camera->SetXY({stage->GetWidth() - game->GetWindowSize().m_x * (1 / camera->GetZoom()), camera->GetXY().m_y});
        }
        if(camera->GetXY().m_y + game->GetWindowSize().m_y * (1 / camera->GetZoom()) > stage->GetHeight()){
            camera->SetXY({camera->GetXY().m_x, stage->GetHeight() - game->GetWindowSize().m_y * (1 / camera->GetZoom())});
        }
        // カメラの範囲がステージより大きいとき  When camera range is larger that stage
        if(game->GetWindowSize().m_x * (1 / camera->GetZoom()) > stage->GetWidth()){
            // 強制的にカメラを中央へ持ってくる  Move the camera forcibly to the center of stage
            camera->SetXY({stage->GetWidth() / 2 - game->GetWindowSize().m_x * (1 / camera->GetZoom()) / 2, camera->GetXY().m_y});
        }
        if(game->GetWindowSize().m_y * (1 / camera->GetZoom()) > stage->GetHeight()){
            camera->SetXY({camera->GetXY().m_x, stage->GetHeight() / 2 - game->GetWindowSize().m_y * (1 / camera->GetZoom()) / 2});
        }
        // 現在の左クリック状態を次のフレームへ引き継ぐ  The current left-click state is carried over to the next frame.
        old_left_button = current_left_button;
        numbers->Add();
        numbers->Delete();
        for(int i = 0; i < my_main::SIMULATION_ACCURACY; i++){
            numbers->CalcAttraction();
            numbers->MoveAll();
            numbers->CalcCollisionAll();
        }
        numbers->DisplayAll();
        pictures->DisplayAll();
        game->Wait();
    }

    // シャットダウン  Shutdown
    game->Shutdown();
    delete game;
    delete textures;
    delete fonts;
    delete text_textures;
    delete pictures;
    delete stage;
    delete numbers;
    // delete stage;
    return 0;
}