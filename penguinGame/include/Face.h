#include <iostream>
#include <GameObject.h>

#pragma once

using std::string;

class Face : public Component{

    public:

        Face(GameObject& associated);
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(string type);

    private:

        int hitpoints;

};
