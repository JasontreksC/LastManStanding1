#pragma once
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"
/*
�� Ŭ������ ����
1. �Ѿ�, ���߿� ���� ��Ʈ�ڽ��� ���忡 �������� ����, �� �Ҹ�.
2. ��Ʈ�ڽ� �� ��������Ʈ �ִϸ��̼� ȿ�� �ߵ�

��Ʈ�ڽ� �߻� ��ġ�� ���ڷ� �޾�, �ش� ��ġ���� �߻�
�Ѿ� ���� ���� �������� �̵�

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

