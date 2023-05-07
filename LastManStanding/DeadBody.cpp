#include "pch.h"
#include "DeadBody.h"

void DeadBody::SetPosOnEnemy(const Enemy& _enemy)
{
	for (int i = 0; i < 6; ++i)
	{
		this->vertexList[i].p.v[0] = _enemy.vertexList[i].p.v[0];
		this->vertexList[i].p.v[1] = _enemy.vertexList[i].p.v[1];
	}
}

void DeadBody::BodyState_Lay()
{
	auto iter = currentSprite.begin();
	currentTexture = *iter;
}

void DeadBody::BodyState_Walk()
{
	auto iter = currentSprite.begin();
	advance(iter, 1);
	currentTexture = *iter;
}

void DeadBody::BodyState_Crawl()
{
	auto iter = currentSprite.begin();
	advance(iter, 2);
	currentTexture = *iter;
}

void DeadBody::SetPosOnPLayer(const Player& _player)
{
	for (int i = 0; i < 6; ++i)
	{
		this->vertexList[i].p.v[0] = _player.vertexList[i].p.v[0];
		this->vertexList[i].p.v[1] = _player.vertexList[i].p.v[1];
	}
}
