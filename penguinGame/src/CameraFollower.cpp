#include "../include/CameraFollower.h"
#include "../include/Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go){
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Update(float dt){
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render(){
    
}

bool CameraFollower::Is(string type){
    return (type == "CameraFollower") ? true : false;
}