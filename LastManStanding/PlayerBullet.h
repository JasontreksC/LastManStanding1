#pragma once
#include "BaseObject.h"
#include "Player.h"

class PlayerBullet : public BaseObject
{
public:
	float BulletStartPosX;

	void PlayerBullet_MoveR(float _speed);
	void PlayerBullet_MoveL(float _speed);
	void SetPositionOnPLayer(const Player& _player);
	bool isPlayerBullet_Finish();
	bool isHeadingRight();
};

