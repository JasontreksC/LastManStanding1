#pragma once
#include "UI.h"

class UIMgr
{
	SINGLETON(UIMgr)
private:
	UIMgr() {}
	~UIMgr() {}

public:
	UI menuBoard;
	UI playButton;
	UI quitButton;
	UI settingsButton;
	UI controlButton;
	
	UI settingBoard;
	UI bgmOnOff;
	UI sfxOnOff;
	UI backButton;

	UI controlBoard;
	UI closeButton;

	bool isBgmOn = true;
	bool isSfxOn = true;

	bool displaySetting = false;
	bool displayControl = false;

public:
	bool Init();
	void Update(HWND _hWnd);
	void Render();
	bool Release();
};

