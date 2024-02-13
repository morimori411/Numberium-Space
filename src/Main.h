#pragma once

#include <string>
#include <SDL.h>
#include <morimori_sdl.h>
#include "Numbers/Numbers.h"
#include "Stage/Stage.h"

namespace my_main{
    // 定数  Constants
    const std::string GAME_TITLE = "Numberium";
    const uint32_t FLAGS_SDL_INIT = SDL_INIT_EVERYTHING; // SDLライブラリの初期化フラグ  Flags for SDL initialization
    const uint32_t FLAGS_IMG_INIT = IMG_INIT_PNG | IMG_INIT_JPG; // SDL_imageライブラリの初期化フラグ  Flags for SDL_image initialization
    const uint32_t WINDOW_FLAGS = SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_BORDERLESS; // ウィンドウ設定のフラグ  Flags for window settings
    const uint32_t RENDERER_FLAGS = 0; // レンダラー設定のフラグ  Flags for renderer settings
    const uint32_t FPS = 60;
    const uint16_t SIMULATION_ACCURACY = 10; // fpsに対する内部フレームの倍率  Internal frame multiplier relative to fps

    const double MAX_CAMERA_ZOOM = 0.2;
    const double CAMERA_ZOOM_STEP = 0.1;
}