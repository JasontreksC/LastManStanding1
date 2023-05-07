#include "pch.h"
#include "Player.h"
#include "TimeMgr.h"

bool Player::Move(float _Xspeed, float _Yspeed)
{
    // 플레이어가 끝에 닿으면 멈춘다.
    if (vertexList[0].p.v[0] <= -0.9f && _Xspeed < 0.0f)
    {
        return false;
    }
    if (vertexList[1].p.v[0] >= 0.9f && _Xspeed > 0.0f)
    {
        return false;
    }

    //if (vertexList[0].p.v[0] + vertexList[1].p.v[0] == 0.000f)
    //    return false;

    // 가로/세로 이동   
    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] += _Xspeed * TimeMgr::GetInst()->GetDeltaTime();
    }

    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[1] += _Yspeed * TimeMgr::GetInst()->GetDeltaTime();
    }
    ObjectPosX += _Xspeed;
    ObjectPosY += _Yspeed;

    return true;
}

bool Player::isCenter()
{
        // 플레이어가 가운데 닿으면 멈춤다.
    if ((vertexList[0].p.v[0] + vertexList[1].p.v[0]) >= -0.1 && (vertexList[0].p.v[0] + vertexList[1].p.v[0]) < 0.01f)
    {
        return true;
    }

    return false;
}

void Player::SetPlayerPos()
{
    while (vertexList[2].p.v[1] >= -0.7f)
    {
        for (int i = 0; i < 6; ++i)
        {
            vertexList[i].p.v[1] -= 0.1f;
        }
    }
    while (vertexList[0].p.v[0] >= -0.1f)
    {
        for (int i = 0; i < 6; ++i)
        {
            vertexList[i].p.v[0] -= 0.1f;
        }
    }
}

void Player::PlayerState_Walk()
{
    SetSprite(L"Player_Walk");

    isCrawling = false;
}

void Player::PlayerState_Crawl()
{
    SetSprite(L"Player_Crawl");

    isCrawling = true;
}

void Player::PlayerState_Attack()
{
    SetSprite(L"Player_Attack");

    isCrawling = false;
}

bool Player::isAttackFisish()
{
    if (currentSprite == *(spriteList.find(L"Player_Attack")->second))
        if (currentTexture == currentSprite.back())
        {
            return true;
        }

    return false;
}

bool Player::isHeadingRight()
{
    if (this->vertexList[0].t.v[0] == 0.0f)
        return true;
    else
        return false;
}
