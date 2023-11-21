#pragma once
struct Vector2
{
	float x;
	float y;
public:
	Vector2() : x(0.f), y(0.f){}
	Vector2(float _x, float _y): x(_x), y(_y){}
	Vector2(int _x, int _y): x(_x), y(_y){}
	Vector2(long _x, long _y) : x(_x), y(_y) {}
	Vector2(POINT _pt) :x((float)_pt.x), y((float)_pt.y) {}
	Vector2& operator=(POINT _pt) {
		x = (float)_pt.x;
		y = (float)_pt.y;
	}
	float Length() { return sqrt(x * x + y * y); }
	Vector2& Normalize() {
		float length = Length();
		assert(length != 0.f);
		x /= length;
		y /= length;
		return *this;
	}
};