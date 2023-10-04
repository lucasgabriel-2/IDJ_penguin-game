#pragma once

class Vec2{

    public:

        float x;
        float y;
        Vec2();
        Vec2(float X, float Y);
        Vec2 GetRotated(float angle);
        Vec2 AddVectors(Vec2 vector1, Vec2 vector2);
};