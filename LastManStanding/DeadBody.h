#pragma once
#include "BaseObject.h"
#include "Player.h"
#include "Enemy.h"

class DeadBody : public BaseObject
{
public:
	void SetPosOnEnemy(const Enemy& _enemy);

	void BodyState_Lay();
	void BodyState_Walk();
	void BodyState_Crawl();
	void SetPosOnPLayer(const Player& _player);

	bool BodyLife = true;
	bool BodyCarrying = false;
	
};

