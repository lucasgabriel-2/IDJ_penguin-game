#include <GameObject.h>

#include <queue>

#pragma once

using std::queue;
using std::weak_ptr;

class Alien : public Component{

    public:

        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);
        double alienAngle;

    private:
        
        enum ActionType{
            MOVE,
            SHOOT
        };

        class Action{
            public:

                Action(ActionType type, float x, float y);
                ActionType type;
                Vec2 pos;

        };

        Vec2 speed;
        int hp;
        int nMinions;
        queue <Action> taskQueue;
        vector <weak_ptr<GameObject> > minionArray;

};
