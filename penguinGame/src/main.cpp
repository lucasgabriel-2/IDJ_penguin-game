#include "../include/Game.h"

int main(int argc, char** argv){
    Game penguinGame = Game::GetInstance();
    penguinGame.Run();
    return 0;
}