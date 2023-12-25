#include <SDL2/SDL_image.h>
#include "../include/Resources.h"
#include "../include/Game.h"

#include <iostream>

using std::string;
using std::cout;

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(string file){
    
    auto exist = imageTable.find(file);

    if (exist != imageTable.end()) {
        return exist->second;
    }else{

        Game& penguinGame = Game::GetInstance();
        SDL_Texture* texture = IMG_LoadTexture(penguinGame.GetRenderer(), &file[0]);

        if (texture == nullptr) {
            SDL_Log("Error in IMG_LoadTexture: %s", SDL_GetError());
            cout << "Error in IMG_LoadTexture" << "\n";
            return nullptr;
        }

        imageTable[file] = texture;
        return texture;
    }

}

void Resources::ClearImages() {
    
    for (auto& pair : imageTable) {
        SDL_Texture* texture = pair.second;
        SDL_DestroyTexture(texture);
    }

    imageTable.clear();
}

void Resources::ClearMusics() {

    for (auto& pair : musicTable) {
        Mix_Music* music = pair.second;
        Mix_FreeMusic(music);
    }

    musicTable.clear();
}

void Resources::ClearSounds() {

    for (auto& pair : soundTable) {
        Mix_Chunk* chunk = pair.second;
        Mix_FreeChunk(chunk);
    }

    soundTable.clear();
}