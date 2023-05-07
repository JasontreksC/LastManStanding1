#pragma once

struct BehaviorState
{
	bool MOVE_RIGHT;
	bool MOVE_LEFT;
	bool MOVE_CRAWL;
	bool ATTACK;
	bool STAY;
	bool CARRY;

	bool HUD_ON;
};

class InputMgr
{
	SINGLETON(InputMgr);
private:
	InputMgr();
	~InputMgr();

public:
	BehaviorState STATE;

public:
	bool Init();
	void Update();
};

