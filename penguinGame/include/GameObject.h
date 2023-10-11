#include "Rect.h"
#include "Component.h"

#include <iostream>
#include <vector>
#include <memory>

#pragma once

using std::string;
using std::vector;
using std::unique_ptr;

class GameObject{

    public:

        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent (string type);
        Rect box;
        bool almostDead;

    private:

        vector <unique_ptr<Component>> components;
        bool isDead;

};
