#include "pch.h"
#include "PlayerBullet.h"
#include "TimeMgr.h"

void PlayerBullet::PlayerBullet_MoveR(float _speed)
{
	for (int i = 0; i < 6; ++i)
	{
		vertexList[i].p.v[0] += _speed * TimeMgr::GetInst()->GetDeltaTime();
	}

	ObjectPosX += _speed * TimeMgr::GetInst()->GetDeltaTime();
}

void PlayerBullet::PlayerBullet_MoveL(float _speed)
{
	for (int i = 0; i < 6; ++i)
	{
		vertexList[i].p.v[0] -= _speed * TimeMgr::GetInst()->GetDeltaTime();
	}

	ObjectPosX -= _speed * TimeMgr::GetInst()->GetDeltaTime();
}

void PlayerBullet::SetPositionOnPLayer(const Player& _player)
{
	for (int i = 0; i < 6; ++i)
	{
		this->vertexList[i].p.v[0] = _player.vertexList[i].p.v[0];
		this->vertexList[i].p.v[1] = _player.vertexList[i].p.v[1];
	}
	BulletStartPosX = this->GetCenterPosX();
}

bool PlayerBullet::isPlayerBullet_Finish()
{
	if (this->GetCenterPosX() - BulletStartPosX >= 0.8f || BulletStartPosX - this->GetCenterPosX() >= 0.8f)
		return true;
	return false;
}

bool PlayerBullet::isHeadingRight()
{
	if (this->vertexList[0].t.v[0] == 0.0f)
		return true;
	else
		return false;
}