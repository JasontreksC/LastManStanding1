#include "pch.h"
#include "TimeMgr.h"

void TimeMgr::Init()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	deltaTime = 0;
	FPS = 0;
	gametime = 0;
}

void TimeMgr::Update()
{
	BOOL isUpdated = QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	deltaTime = ((double)curTime.QuadPart - (double)lastTime.QuadPart) / (double)periodFrequency.QuadPart;

	static float frames = 0.0f;
	static double oneSec = 0.0f;

	frames += 1.0f;
	oneSec += deltaTime;
	gametime += deltaTime;
	if (oneSec >= 1.0f)
	{
		FPS = frames;

		frames = 0;
		oneSec = 0;
	}

	lastTime = curTime;
}

double TimeMgr::GetDeltaTime()
{
	return deltaTime;
}

int TimeMgr::GetFPS()
{
	return (int)FPS;
}

float TimeMgr::GetGametime()
{
	return gametime;
}
