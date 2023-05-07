#pragma once

class TimeMgr
{
	SINGLETON(TimeMgr);
private:
	TimeMgr() {};
	~TimeMgr() {};

public:
	LARGE_INTEGER periodFrequency;
	LARGE_INTEGER lastTime;
	LARGE_INTEGER curTime;

	double deltaTime = 0;
	float FPS = 0;
	float gametime = 0;

	void Init();
	void Update();

	double GetDeltaTime();
	int GetFPS();
	float GetGametime();
};

