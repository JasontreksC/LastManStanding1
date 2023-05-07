#include "pch.h"
#include "GameCore.h"

WINDOW_MAIN
{
	GameCore::GetInst()->Init(hInstance, L"LAST MAN STANDING", 1280, 800);

	//SoundMgr::GetInst()->AddFmodSound("../res/Sounds/Libertad.mp3", "MainMusic", FMOD_LOOP_NORMAL); // 1
	//SoundMgr::GetInst()->AddFmodSound("../res/Sounds/DaysGone.mp3", "MainMusic", FMOD_LOOP_NORMAL); // 2
	SoundMgr::GetInst()->AddFmodSound("../res/Sounds/RidingNOMAD.mp3", "MainMusic", FMOD_LOOP_NORMAL); // 3 
	//SoundMgr::GetInst()->AddFmodSound("../res/Sounds/Supermarine.mp3", "MainMusic", FMOD_LOOP_NORMAL); // 4

	bool OpenGame = true;
	bool RunGame = true;
	// Scene : Openning Game

	SoundMgr::GetInst()->PlayFmodSound("MainMusic", "BGM");
	while (OpenGame)
	{
		GameCore::GetInst()->RenderOpening(OpenGame, RunGame);
	}
    // Scene : StartGame
	while (RunGame)
	{
		TimeMgr::GetInst()->Init();
		GameCore::GetInst()->GameInit();
		GameCore::GetInst()->Frame(RunGame);
		GameCore::GetInst()->GameRelease();
	}
}
