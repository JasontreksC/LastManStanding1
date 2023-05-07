#pragma once
#include "BaseObject.h"

class World : public BaseObject
{
public:
	bool isLeftEnd();
	bool isRightEnd();

	void SetWorldPos();
	float GetLeftEndPos_X();
	float GetLeftEndPos_Y();

	virtual bool Move(float _Xspeed, float _Yspeed);
};

