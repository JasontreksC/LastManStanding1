#include "pch.h"
#include "Enemy.h"

bool Enemy::isSoldierDead()
{
	if (SoldierLife == false)
		return true;
	return false;
}

bool Enemy::isBommerGone()
{
	if (vertexList[1].p.v[0] <= -1.0f)
		return true;
	return false;
}

bool Enemy::isSpriteName(wstring _spriteName)
{
	if (currentSprite == *(spriteList.find(_spriteName)->second))
		return true;
	else
		return false;
}
