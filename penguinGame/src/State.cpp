#include "../include/State.h"
#include "../include/Face.h"
#include "../include/Vec2.h"
#include "../include/Sound.h"

#include "../include/Sprite.h"
#include "../include/TileMap.h"
#include "../include/TileSet.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"

#define PI  M_PI

State::State(){

    quitRequested = false;

	GameObject* bg = new GameObject();
	Sprite* bgSprite = new Sprite(*bg,"img/ocean.jpg");
	bg->AddComponent(bgSprite);
	bg->box.x = 0;
	bg->box.y = 0;
	objectArray.emplace_back(bg);

	GameObject *gameTiles = new GameObject();
	TileSet* gameTileSet = new TileSet (64, 64, "img/tileset.png");
	TileMap* gameTileMap = new TileMap(*gameTiles, "map/tileMap.txt", gameTileSet);
	gameTiles->AddComponent(gameTileMap);
	gameTiles->box.x = 0;
	gameTiles->box.y = 0;	
	objectArray.emplace_back(gameTiles);

    music = new Music("audio/stageState.ogg");
    
}

State::~State(){

    objectArray.clear();
    delete(bg);
    delete(music);

}

void State::LoadAssets(){
    
    music->Play();
}

void State::Update(float dt){

    Camera::Update(dt);

    InputManager& inputManager = InputManager::GetInstance();

    if(inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested()){
        quitRequested = true;
    }

    if(inputManager.KeyPress(SPACE_BAR)){
		
		int mouseX = inputManager.GetMouseX();
		int mouseY = inputManager.GetMouseY();
		Vec2 objPos;
		objPos = objPos.AddVectors(Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ), Vec2( mouseX - Camera::pos.x , mouseY - Camera::pos.y));
		AddObject((int)objPos.x - Camera::pos.x, (int)objPos.y - Camera::pos.y);
    }

    for(long unsigned int i = 0; i < objectArray.size(); i++){
		
        objectArray[i]->Update(dt);  

    }


    for(long unsigned int i = 0; i < objectArray.size(); i++){
        if(objectArray[i]->IsDead() && !objectArray[i]->almostDead){
            objectArray.erase(objectArray.begin()+i);
        }        
    }

}

void State::Render(){

    for(long unsigned int i = 0; i < objectArray.size(); i++){
        if(objectArray[i]->GetComponent("TileMap") != nullptr){
            objectArray[i]->box.x = Camera::pos.x;
            objectArray[i]->box.y = Camera::pos.y;
        }
        objectArray[i]->Render();        
    }

}

bool State::QuitRequested(){

    return quitRequested;
}

// void State::Input() {
// 	SDL_Event event;
// 	int mouseX, mouseY;

// 	// Obtenha as coordenadas do mouse
// 	SDL_GetMouseState(&mouseX, &mouseY);

// 	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
// 	while (SDL_PollEvent(&event)) {

// 		// Se o evento for quit, setar a flag para terminação
// 		if(event.type == SDL_QUIT) {
// 			quitRequested = true;
// 		}
		
// 		// Se o evento for clique...
// 		if(event.type == SDL_MOUSEBUTTONDOWN) {

// 			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
// 			for(int i = objectArray.size() - 1; i >= 0; --i) {
// 				// Obtem o ponteiro e casta pra Face.
// 				GameObject* go = (GameObject*) objectArray[i].get();
// 				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
// 				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
// 				// ao usar get(), violamos esse princípio e estamos menos seguros.
// 				// Esse código, assim como a classe Face, é provisório. Futuramente, para
// 				// chamar funções de GameObjects, use objectArray[i]->função() direto.

// 				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
// 					Face* face = (Face*)go->GetComponent( "Face" );
// 					if ( nullptr != face ) {
// 						// Aplica dano
// 						face->Damage(std::rand() % 10 + 10);
// 						// Sai do loop (só queremos acertar um)
// 						break;
// 					}
// 				}
// 			}
// 		}
// 		if( event.type == SDL_KEYDOWN ) {
// 			// Se a tecla for ESC, setar a flag de quit
// 			if( event.key.keysym.sym == SDLK_ESCAPE ) {
// 				quitRequested = true;
// 			}
// 			// Se não, crie um objeto
// 			else {
// 				Vec2 objPos;
// 				objPos = objPos.AddVectors(Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ), Vec2( mouseX, mouseY ));
// 				AddObject((int)objPos.x, (int)objPos.y);
// 			}
// 		}
// 	}
// }

void State::AddObject(int mouseX, int mouseY){
    
    GameObject* firstEnemy = new GameObject();
	Sprite* enemyImage = new Sprite(*firstEnemy,"img/penguinface.png");
	firstEnemy->AddComponent(enemyImage);

	firstEnemy->box.x = mouseX - Camera::pos.x ;
	firstEnemy->box.y = mouseY - Camera::pos.y;

    Sound* enemySound = new Sound(*firstEnemy,"audio/boom.wav");;
	firstEnemy->AddComponent(enemySound);
    
    Face* enemyFace = new Face(*firstEnemy);
    firstEnemy->AddComponent(enemyFace);

    objectArray.emplace_back(firstEnemy);
}   