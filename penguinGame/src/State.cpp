#include "../include/State.h"
#include "../include/Face.h"
#include "../include/Vec2.h"
#include "../include/Sound.h"

#include "../include/Sprite.h"

#define PI 3.14159265358979323846

State::State(){

    quitRequested = false;

	GameObject* bg = new GameObject();
	Sprite* bgSprite = new Sprite(*bg,"img/ocean.jpg");;
	bg->AddComponent(bgSprite);

	bg->box.x = 0;
	bg->box.y = 0;

	objectArray.emplace_back(bg);

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

    Input();

    for(long unsigned int i = 0; i < objectArray.size(); i++){
		
        objectArray[i]->Update(dt);  

    }


    for(long unsigned int i = 0; i < objectArray.size(); i++){
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin()+i);
        }        
    }

}

void State::Render(){

    for(long unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();        
    }

}

bool State::QuitRequested(){

    return quitRequested;
}

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos;
				objPos = objPos.AddVectors(Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ), Vec2( mouseX, mouseY ));
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}

void State::AddObject(int mouseX, int mouseY){
    	
    GameObject* firstEnemy = new GameObject();
	Sprite* enemyImage = new Sprite(*firstEnemy,"img/penguinface.png");
	firstEnemy->AddComponent(enemyImage);

	firstEnemy->box.x = mouseX;
	firstEnemy->box.y = mouseY;
	// firstEnemy->box.w = 100;
	// firstEnemy->box.h = 100;

    Sound* enemySound = new Sound(*firstEnemy,"audio/boom.wav");;
	firstEnemy->AddComponent(enemySound);
    
    Face* enemyFace = new Face(*firstEnemy);
    firstEnemy->AddComponent(enemyFace);

    objectArray.emplace_back(firstEnemy);
}   