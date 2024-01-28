#include "Main.h"

int main(int argc, char* argv[]){
    game::Game* game = new game::Game;
    game->Initialize();
    pictures::Textures* textures = new pictures::Textures(game);
    pictures::Fonts* fonts = new pictures::Fonts;
    pictures::TextTextures* text_textures = new pictures::TextTextures(game, fonts);
    pictures::Camera* camera = new pictures::Camera;
    pictures::Pictures* pictures = new pictures::Pictures(game, textures, text_textures, camera);
    stage::Stage* stage = new stage::Stage(game, 1080, 1920);
    numbers::Numbers* numbers = new numbers::Numbers(game, pictures, stage);

    // メインループ  Main loop
    SDL_Event event;
    fonts->LoadFont("data/fonts/MPLUS1Code-Regular.ttf");
    while(game->GetIsRunning()){
        // SDL_Event
        while(SDL_PollEvent(&event)){
            // ゲーム終了  End of game
            if(event.type == SDL_QUIT) game->SetIsRunning(false);
        }

        numbers->Add();
        numbers->Delete();
        for(int i = 0; i < game::SIMULATION_ACCURACY; i++){
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