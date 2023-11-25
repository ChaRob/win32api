#pragma once
struct Vector2
{
	float x;
	float y;
public:
	Vector2() : x(0.f), y(0.f){}
	Vector2(float _x, float _y): x((float)_x), y((float)_y){}
	Vector2(int _x, int _y): x((float)_x), y((float)_y){}
	Vector2(long _x, long _y) : x((float)_x), y((float)_y) {}
	Vector2(POINT _pt) :x((float)_pt.x), y((float)_pt.y) {}
	Vector2& operator=(POINT _pt) {
		x = (float)_pt.x;
		y = (float)_pt.y;
	}
	Vector2 operator+(const POINT _pt) {
		return Vector2(x + (float)_pt.x, y + (float)_pt.y);
	}
	Vector2 operator+(const Vector2& _pt) {
		return Vector2(x + (float)_pt.x, y + (float)_pt.y);
	}
	Vector2 operator-(const POINT _pt) {
		return Vector2(x - (float)_pt.x, y - (float)_pt.y);
	}
	Vector2 operator-(const Vector2& _pt) {
		return Vector2(x - (float)_pt.x, y - (float)_pt.y);
	}
	Vector2 operator*(const POINT& _pt) {
		return Vector2(x * (float)_pt.x, y * (float)_pt.y);
	}
	Vector2 operator*(const Vector2& _pt) {
		return Vector2(x * (float)_pt.x, y * (float)_pt.y);
	}
	Vector2 operator*(const int _pt) {
		return Vector2(x * _pt, y * _pt);
	}
	Vector2 operator*(const float _pt) {
		return Vector2(x * _pt, y * _pt);
	}
	Vector2 operator/(const int _pt) {
		return Vector2(x / _pt, y / _pt);
	}
	Vector2 operator/(const float _pt) {
		return Vector2(x / _pt, y / _pt);
	}
	float Length() { return sqrtf(x * x + y * y); }
	Vector2& Normalize() {
		float length = Length();
		//assert(length != 0.f);
		if (length == 0) {
			return *this;
		}
		x /= length;
		y /= length;
		return *this;
	}
};