#include "pch.h"
#include "World.h"
#include "TimeMgr.h"

bool World::isLeftEnd()
{
    if (vertexList[0].p.v[0] >= -1.1f)
    {
        return true;
    }
    return false;
}

bool World::isRightEnd()
{
    if (vertexList[1].p.v[0] <= 1.1f)
    {
        return true;
    }
    return false;
}

void World::SetWorldPos()
{
    // 세로 높이 조정
    float term = 0.0f;

    if (vertexList[2].p.v[1] < -1.0f)
    {
        term = vertexList[2].p.v[1] + 1.0f;
    }

    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[1] -= term;
    }

    // 왼쪽 끝에서 시작
    while (!isLeftEnd())
    {
        for (int i = 0; i < 6; ++i)
        {
            vertexList[i].p.v[0] += 0.1f;
        }
    }
}

float World::GetLeftEndPos_X()
{
    return vertexList[0].p.v[0];
}

float World::GetLeftEndPos_Y()
{
    return vertexList[0].p.v[1];
}

bool World::Move(float _Xspeed, float _Yspeed)
{
    // 월드의 끝에 닿으면 멈춘다.
    if (vertexList[0].p.v[0] >= -1.1f && _Xspeed < 0.0f)
    {
        return false;
    }
    if (vertexList[1].p.v[0] <= 1.1f && _Xspeed > 0.0f)
    {
        return false;
    }

    // 가로/세로 이동   
    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[0] -= _Xspeed * TimeMgr::GetInst()->GetDeltaTime();;
    }

    for (int i = 0; i < 6; ++i)
    {
        vertexList[i].p.v[1] -= _Yspeed * TimeMgr::GetInst()->GetDeltaTime();;
    }
    ObjectPosX += _Xspeed;
    ObjectPosY += _Yspeed;

    return true;
}
