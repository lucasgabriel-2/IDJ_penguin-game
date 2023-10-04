#include "Vec2.h"

#pragma once

class Rect{

    public:
        
        float x;
        float y;
        float w;
        float h;

        Rect();
        Rect(float X, float Y, float W, float H);
        bool Contains(Vec2 vec);


};