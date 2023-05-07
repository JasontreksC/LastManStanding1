#include "pch.h"
#include "Collision.h"
#include "TimeMgr.h"

bool Collision::isBulletFinish()
{
	if (BulletStartPosX - this->GetCenterPosX() >= 0.8f)
		return true;

	return false;
}

bool Collision::isBombFinish()
{
	if (currentTexture == currentSprite.back())
		return true;

	return false;
}

void Collision::BulletMove(float _speed)
{
	for (int i = 0; i < 6; ++i)
	{
		vertexList[i].p.v[0] -= _speed * TimeMgr::GetInst()->GetDeltaTime();
	}

	ObjectPosX -= _speed * TimeMgr::GetInst()->GetDeltaTime();
}

void Collision::SetPosOnEnemy(const Enemy& _enemy)
{
	if (this->hitboxType == HitboxType::BULLET)
	{
		for (int i = 0; i < 6; ++i)
		{
			this->vertexList[i].p.v[0] = _enemy.vertexList[i].p.v[0];
			this->vertexList[i].p.v[1] = _enemy.vertexList[i].p.v[1];
		}
		BulletStartPosX = this->GetCenterPosX();
	}
	else if (this->hitboxType == HitboxType::BOMB)
	{
		for (int i = 0; i < 6; ++i)
		{
			this->vertexList[i].p.v[0] = _enemy.vertexList[i].p.v[0] + 0.2f;
			this->vertexList[i].p.v[1] = _enemy.vertexList[i].p.v[1] - 0.55f;
		}
	}

}

bool Collision::HitPlayer(Player& _player, bool _isCrawl)
{
	if (_player.isVictory == true)
		return false;

	switch (hitboxType)
	{
		case HitboxType::BULLET:
		{
			if (this->GetLeftPosX() - _player.GetCenterPosX() <= 0.02f &&
				_player.GetCenterPosX() - this->GetLeftPosX() <= 0.02f)
			{
				if (_player.carryingBody == true && _player.isHeadingRight() == false)
					return false;
				else if (_isCrawl == true)
					return false;
				else
				{
					_player.playerLife -= 1;
					return true;
				}
			}
		} break;

		case HitboxType::BOMB:
		{
			if (this->spriteIndex > 40 || this->spriteIndex < 10)
				return false;
			if (this->GetLeftPosX() <= _player.GetLeftPosX() &&
				_player.GetRightPosX() <= this->GetRightPosX())
			{
				if (_player.carryingBody == true && _isCrawl == true)
				{
					return false;
				}
				else
				{

					_player.playerLife -= 1;
					return true;
				}
			}
		} break;
	}
}