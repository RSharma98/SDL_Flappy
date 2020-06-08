#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
	float x, y;
	Vector2();
	Vector2(float a);
	Vector2(float x, float y);

	Vector2 operator*(float n);
	Vector2 operator+(Vector2 v);
	void operator+=(Vector2 v);
};

#endif // !VECTOR2_H