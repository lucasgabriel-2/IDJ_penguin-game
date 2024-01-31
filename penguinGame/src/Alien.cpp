#include "../include/Alien.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Minion.h"
#include "../include/State.h"
#include "../include/Game.h"

#include <cmath>

using std::sqrt;
using std::pow;
using std::abs;
using std::shared_ptr;

Alien::Action::Action(ActionType type, float x, float y) : type(type), pos(x, y) {
    
}

Alien::Alien(GameObject& associated, int nMinions) : Component (associated){

    this->nMinions = nMinions;
    Sprite* alienSprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(alienSprite);

    speed.x = 100;
    speed.y = 100;
    hp = 100;

}

void Alien::Start(){

    State& gameState = Game::GetInstance().GetState();
    weak_ptr <GameObject> alienCenter = gameState.GetObjectPtr(&associated);

    for(int i = 0; i < nMinions; i++){
        GameObject* newMinion  = new GameObject();
        float arcOffsetDeg = i * 360.0/nMinions;
        Minion *minion = new Minion(*newMinion, alienCenter, arcOffsetDeg);
        newMinion->AddComponent(minion);
        minionArray.push_back(gameState.AddObject(newMinion));
    }
}

Alien::~Alien(){

    for(int i = minionArray.size()-1; i >= 0; i--){
        minionArray.erase(minionArray.begin()+i);
    }

    minionArray.clear();
}

void Alien::Update(float dt){
    InputManager& inputManager = InputManager::GetInstance();

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
        int mouseX = inputManager.GetMouseX();
        int mouseY = inputManager.GetMouseY();

        Vec2 objPos;
        objPos.x = mouseX + Camera::pos.x;
        objPos.y = mouseY + Camera::pos.y;

        Action action(ActionType::SHOOT, objPos.x, objPos.y);
        taskQueue.push(action);
    }

    if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)){
        int mouseX = inputManager.GetMouseX();
        int mouseY = inputManager.GetMouseY();
        
        Vec2 objPos;
        objPos.x = mouseX + Camera::pos.x;
        objPos.y = mouseY + Camera::pos.y;

        Action action(ActionType::MOVE, objPos.x, objPos.y);
        taskQueue.push(action);
    }

    if(!taskQueue.empty()){
        Action& currentAction = taskQueue.front();

        if(currentAction.type == ActionType::MOVE){

            Vec2 alienSpeed;
            alienSpeed.x = 100;
            alienSpeed.y = 100;

            float dx = currentAction.pos.x - (associated.box.x + associated.box.w / 2);
            float dy = currentAction.pos.y - (associated.box.y + associated.box.h / 2);
            float distance = sqrt(pow(dx, 2) + pow(dy, 2));

            if(distance <= sqrt(pow(alienSpeed.x*dt, 2) + pow(alienSpeed.y*dt, 2))){
                associated.box.x = currentAction.pos.x - associated.box.w / 2;
                associated.box.y = currentAction.pos.y - associated.box.h / 2;
                taskQueue.pop();
            }else{
                float angle = atan2(dy, dx);
                alienSpeed.x = cos(angle) * speed.x;
                alienSpeed.y = sin(angle) * speed.y;

                associated.box.x += alienSpeed.x * dt;
                associated.box.y += alienSpeed.y * dt;
            }
            
        }else if(currentAction.type == ActionType::SHOOT){

            int randomMinion = std::rand() % nMinions;
            shared_ptr<GameObject> sharedMinion = minionArray[randomMinion].lock();
            Minion* shooterMinion = (Minion*) sharedMinion->GetComponent("Minion");
            shooterMinion->Shoot(currentAction.pos);

            taskQueue.pop();
        }
    }

    if(hp <= 0){
        associated.RequestDelete();
    }
}

void Alien::Render(){

}

bool Alien::Is(string type){
    return (type == "Alien") ? true : false;
}
