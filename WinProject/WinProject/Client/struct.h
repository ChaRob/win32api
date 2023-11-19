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
};