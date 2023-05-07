#include "pch.h"
#include "InputMgr.h"

InputMgr::InputMgr()
{

}
InputMgr::~InputMgr()
{

}


bool InputMgr::Init()
{
	STATE.MOVE_RIGHT = false;
	STATE.MOVE_LEFT = false;
	STATE.MOVE_CRAWL = false;
	STATE.ATTACK = false;
	STATE.STAY = true;
	STATE.CARRY = false;
	STATE.HUD_ON = false;

	return true;
}

void InputMgr::Update()
{
	if (GetAsyncKeyState('Q') & 0x0001)
	{
		STATE.HUD_ON = !STATE.HUD_ON;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001) // Attack
	{
		STATE.ATTACK = true;
		STATE.MOVE_RIGHT = false;
		STATE.MOVE_LEFT = false;
		STATE.MOVE_CRAWL = false;
	}

	if (STATE.ATTACK == false)
	{
		if (GetAsyncKeyState('D') & 0x8000) // Hold
			STATE.MOVE_RIGHT = true;
		else
			STATE.MOVE_RIGHT = false;

		if (GetAsyncKeyState('A') & 0x8000)
			STATE.MOVE_LEFT = true;
		else
			STATE.MOVE_LEFT = false;

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			STATE.MOVE_CRAWL = true;
		else
			STATE.MOVE_CRAWL = false;

		if (GetAsyncKeyState(VK_RBUTTON) & 0x0001) // SŰ
			STATE.CARRY = true;
	}

}
