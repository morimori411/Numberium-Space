#include "Main.h"

int main(int argc, char* argv[]){
    game::Game* game = new game::Game;
    game->Initialize();
    pictures::Textures* textures = new pictures::Textures(game);
    pictures::Fonts* fonts = new pictures::Fonts;
    pictures::TextTextures* text_textures = new pictures::TextTextures(game, fonts);
    pictures::Pictures* pictures = new pictures::Pictures(game, textures, text_textures);
    stage::Stage* stage = new stage::Stage(game, 500, 500);
    numbers::Numbers* numbers = new numbers::Numbers(pictures, stage);

    // メインループ  Main loop
    SDL_Event event;
    while(game->GetIsRunning()){
        // SDL_Event
        while(SDL_PollEvent(&event)){
            // ゲーム終了  End of game
            if(event.type == SDL_QUIT) game->SetIsRunning(false);
        }

        numbers->Add();
        numbers->Delete();
        numbers->CalcAttraction();
        numbers->MoveAll();
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
    delete numbers;
    // delete stage;
    return 0;
}