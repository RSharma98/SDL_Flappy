#include "Vector2.h"

///Default constructor
Vector2::Vector2() {
	x = y = 0;
}

///Constructor where both x and y have the same values
Vector2::Vector2(float a) {
	x = y = a;
}

///Constructor to set x and y
Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator*(float n) {
	return Vector2(x * n, y * n);
}

Vector2 Vector2::operator+(Vector2 v)
{
	return Vector2(x + v.x, y + v.y);
}

void Vector2::operator+=(Vector2 v) {
	x += v.x;
	y += v.y;
}
