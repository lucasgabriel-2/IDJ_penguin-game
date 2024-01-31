#include "../include/State.h"
// #include "../include/Face.h"
#include "../include/Vec2.h"
#include "../include/Sound.h"

#include "../include/Sprite.h"
#include "../include/TileMap.h"
#include "../include/TileSet.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"
#include "../include/Alien.h"

#define PI  M_PI

State::State(){

    quitRequested = false;
    started = false;

	GameObject* bg = new GameObject();
	Sprite* bgSprite = new Sprite(*bg,"img/ocean.jpg");
	bg->AddComponent(bgSprite);
	bg->box.x = 0;
	bg->box.y = 0;
	objectArray.emplace_back(bg);

    CameraFollower* cameraFollower = new CameraFollower(*bg);
    bg->AddComponent(cameraFollower);
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

    GameObject *alienGameObject = new GameObject();
    Alien *alien = new Alien(*alienGameObject, 3);
    alienGameObject->AddComponent(alien);
    alienGameObject->box.x = 512;
    alienGameObject->box.y = 300;
	objectArray.emplace_back(alienGameObject);

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
		
		// int mouseX = inputManager.GetMouseX();
		// int mouseY = inputManager.GetMouseY();
		// Vec2 objPos;
		// objPos = objPos.AddVectors(Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ), Vec2( mouseX , mouseY));
		// AddObject((int)objPos.x, (int)objPos.y);
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

// void State::AddObject(int mouseX, int mouseY){
    
//     GameObject* firstEnemy = new GameObject();
// 	Sprite* enemyImage = new Sprite(*firstEnemy,"img/penguinface.png");
// 	firstEnemy->AddComponent(enemyImage);

// 	firstEnemy->box.x = mouseX + Camera::pos.x ;
// 	firstEnemy->box.y = mouseY + Camera::pos.y;

//     Sound* enemySound = new Sound(*firstEnemy,"audio/boom.wav");
// 	firstEnemy->AddComponent(enemySound);
    
//     Face* enemyFace = new Face(*firstEnemy);
//     firstEnemy->AddComponent(enemyFace);

//     objectArray.emplace_back(firstEnemy);
// }   

void State::Start(){
    
    LoadAssets();
    for(auto& obj : objectArray){
        obj->Start();
    }
    started = true;

}

weak_ptr <GameObject> State::AddObject(GameObject* go){

    shared_ptr<GameObject> objectSharedPointer(go);
    objectArray.push_back(objectSharedPointer);
    
    if(started){
        objectSharedPointer->Start();
    }
    
    return weak_ptr<GameObject>(objectSharedPointer);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){

    for(auto& object : objectArray) {
        if(object.get() == go) {
            return weak_ptr<GameObject>(object);
        }
    }
    
    return weak_ptr<GameObject>();
}
