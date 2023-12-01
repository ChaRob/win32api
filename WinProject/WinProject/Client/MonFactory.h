#pragma once

class Monster;

enum class MON_TYPE {
	NORMAL,
	RANGE,
};

class MonFactory
{
private:
	MonFactory(){}
	~MonFactory(){}

private:


public:
	static Monster* CreateMonster(MON_TYPE _type, Vector2 _pos);
};

