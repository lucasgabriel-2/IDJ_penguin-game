#include "GameObject.h"

#pragma once

using std::string;

class CameraFollower : public Component{

    public:

        CameraFollower(GameObject& go);
        void Update(float dt);
        void Render();
        bool Is(string type);

};