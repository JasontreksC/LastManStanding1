#pragma once
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
/*
이 클래스의 역할
1. 총알, 폭발에 의한 히트박스를 월드에 동적으로 생성, 및 소멸.
2. 히트박스 내 스프라이트 애니메이션 효과 발동

히트박스 발생 위치를 인자로 받아, 해당 위치에서 발생
총알 같은 경우는 왼쪽으로 이동

*/
enum class HitboxType
{
	BULLET,
	BOMB
};

class Collision : public BaseObject
{	
public:
	float BulletStartPosX;

	HitboxType hitboxType;
	bool isBulletFinish();
	bool isBombFinish();

	void BulletMove(float _speed);
	void SetPosOnEnemy(const Enemy& _enemy);
	bool HitPlayer(Player& _player, bool _isCrawl);

	bool operator==(const Collision& _other) { return currentTexture == _other.currentTexture; }
};

