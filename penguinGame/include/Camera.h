#include "GameObject.h"

#pragma once

class Camera{

    public:

        static void Follow(GameObject* newFocous);
        static void UnFollow();
        static void Update(float dt);
        static Vec2 pos;
        static Vec2 speed;

    private:

        static GameObject* focus;

};