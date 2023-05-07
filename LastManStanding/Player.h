#pragma once
#include "BaseObject.h"

class Player : public BaseObject
{
	friend class DeadBody;
	friend class PlayerBullet;
public:
	virtual bool Move(float _Xspeed, float _Yspeed);
	bool isCenter();

	void SetPlayerPos();
	void PlayerState_Walk();
	void PlayerState_Crawl();
	void PlayerState_Attack();

	//void Animate_Walk(float _speed);
	//void Animate_Crawl(float _speed);
	//void Animate_Attack(float _speed);
	bool isAttackFisish();

	bool isHeadingRight();

public:
	bool isCrawling = false;
	int playerLife = 1;
	float walkFrame;
	float crawlFrame;
	float attackFrame;
	bool carryingBody = false;

	bool isVictory = false;
};

