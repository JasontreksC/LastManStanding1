#pragma once
#include "BaseObject.h"

enum class EnemyType
{
	SOLDIER,
	BOMMER
};

class Enemy : public BaseObject
{
	friend class Collision;
	friend class DeadBody;
public:
	bool SoldierLife = true;
	EnemyType enemyType;
	bool isSoldierDead();
	bool isBommerGone();
	bool isSpriteName(wstring _spriteName);
};

