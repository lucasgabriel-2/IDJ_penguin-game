#include "../include/Vec2.h"
#include <math.h>

Vec2::Vec2(){
	x = 0;
	y = 0;
}

Vec2::Vec2(float X, float Y){

    x = X;
    y = Y;
    
}

Vec2 Vec2::GetRotated(float angle) {

	float X = this->x * cos(angle) - this->y * sin(angle);
	float Y = this->y * cos(angle) + this->x * sin(angle);

	return Vec2(X, Y);

}

Vec2 Vec2::AddVectors(Vec2 vector1, Vec2 vector2) {

	Vec2 sum;
	sum.x = vector1.x + vector2.x;
	sum.y = vector1.y + vector2.y;
	return sum;
}