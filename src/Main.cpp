#include "Main.h"

int main(int argc, char* argv[]){
    game::Game* game = new game::Game;
    game->Initialize();
    pictures::Textures* textures = new pictures::Textures(game);
    pictures::Fonts* fonts = new pictures::Fonts;
    pictures::TextTextures* text_textures = new pictures::TextTextures(game, fonts);
    pictures::Pictures* pictures = new pictures::Pictures(game, textures, text_textures);
    numbers::Numbers* numbers = new numbers::Numbers;
    stage::Stage* stage = new stage::Stage;
    numbers::Number* number = new numbers::Number(pictures, 0, 100, common::Vec2(100, 100));

    // メインループ  Main loop
    SDL_Event event;
    while(game->GetIsRunning()){
        // SDL_Event
        while(SDL_PollEvent(&event)){
            // ゲーム終了  End of game
            if(event.type == SDL_QUIT) game->SetIsRunning(false);
        }
        number->Move();
        number->Display();
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
    delete numbers;
    delete stage;
    return 0;
}