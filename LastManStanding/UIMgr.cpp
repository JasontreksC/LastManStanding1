#include "pch.h"
#include "UIMgr.h"

bool UIMgr::Init()
{
	if (menuBoard.Create(L"BasicShader.txt") == false)
		return false;
	menuBoard.MakeSprite(L"Menu_Default", L"../res/UI/MenuBoard", 1, L".png");
	menuBoard.SetObjScale_ByTextureSize();

	if (playButton.Create(L"BasicShader.txt") == false)
		return false;
	playButton.MakeSprite(L"PLAY", L"../res/UI_PLAY/Frame_", 11, L".png");
	playButton.SetObjScale_ByTextureSize();

	if (quitButton.Create(L"BasicShader.txt") == false)
		return false;
	quitButton.MakeSprite(L"QUIT", L"../res/UI_QUIT/Frame_", 11, L".png");
	quitButton.SetObjScale_ByTextureSize();

	if (settingsButton.Create(L"BasicShader.txt") == false)
		return false;
	settingsButton.MakeSprite(L"SETTINGS", L"../res/UI_SETTINGS/Frame_", 11, L".png");
	settingsButton.SetObjScale_ByTextureSize();

	if (controlButton.Create(L"BasicShader.txt") == false)
		return false;
	controlButton.MakeSprite(L"CONTROL", L"../res/UI_CONTROL/Frame_", 11, L".png");
	controlButton.SetObjScale_ByTextureSize();

	menuBoard.AddChild(L"PLAY", playButton);
	menuBoard.AddChild(L"QUIT", quitButton);
	menuBoard.AddChild(L"SETTINGS", settingsButton);
	menuBoard.AddChild(L"CONTROL", controlButton);

	menuBoard.SetObjScale_ByManual(0.5f);
	menuBoard.MakeLonger();
	for (auto child : menuBoard.childUI)
	{
		child.second->SetObjScale_ByManual(0.5f);
	}
	menuBoard.SetPos_InNDC(-1.0f, 1.0f);
	menuBoard.SetChildsVertical();

	//==++++++++++++++++++++++++++++++==

	if (settingBoard.Create(L"BasicShader.txt") == false)
		return false;
	settingBoard.MakeSprite(L"Menu_Settings", L"../res/UI/MenuBoard", 1, L".png");
	settingBoard.SetObjScale_ByTextureSize();

	if (bgmOnOff.Create(L"BasicShader.txt") == false)
		return false;
	bgmOnOff.MakeSprite(L"BGM_ON", L"../res/BGM/BGM_ON", 1, L".png");
	bgmOnOff.MakeSprite(L"BGM_OFF", L"../res/BGM/BGM_OFF", 1, L".png");
	bgmOnOff.SetObjScale_ByTextureSize();

	if (sfxOnOff.Create(L"BasicShader.txt") == false)
		return false;

	sfxOnOff.MakeSprite(L"SFX_ON", L"../res/SFX/SFX_ON", 1, L".png");
	sfxOnOff.MakeSprite(L"SFX_OFF", L"../res/SFX/SFX_OFF", 1, L".png");
	sfxOnOff.SetObjScale_ByTextureSize();

	if (backButton.Create(L"BasicShader.txt") == false)
		return false;

	backButton.MakeSprite(L"BACK", L"../res/UI_BACK/Frame_", 11, L".png");
	backButton.SetObjScale_ByTextureSize();


	settingBoard.AddChild(L"BGM", bgmOnOff);
	settingBoard.AddChild(L"SFX", sfxOnOff);
	settingBoard.AddChild(L"BACK", backButton);

	settingBoard.SetObjScale_ByManual(0.5f);
	settingBoard.MakeLonger();
	for (auto child : settingBoard.childUI)
	{
		child.second->SetObjScale_ByManual(0.5f);
	}
	settingBoard.SetPos_InNDC(-0.69f, 1.0f);
	settingBoard.SetChildsVertical();

	// ==++++++++++++++++++++++++++++++++++++==
	if (controlBoard.Create(L"BasicShader.txt") == false)
		return false;
	controlBoard.MakeSprite(L"ControlBoard", L"../res/UI/ControlBoard", 1, L".jpeg");
	controlBoard.SetObjScale_ByTextureSize();
	controlBoard.SetObjScale_ByManual(0.4f);

	if (closeButton.Create(L"BasicShader.txt") == false)
		return false;
	closeButton.MakeSprite(L"Close", L"../res/UI/ControlClose", 1, L".png");
	closeButton.SetObjScale_ByTextureSize();
	closeButton.SetObjScale_ByManual(0.5f);
	closeButton.SetPos_InNDC(controlBoard.GetLeftPosX(), controlBoard.GetBottomPosY());

	controlBoard.AddChild(L"Close", closeButton);
}

void UIMgr::Update(HWND _hWnd)
{
	for (auto ui : menuBoard.childUI)
	{
		if (ui.second->isCursorOn(_hWnd))
		{
			if (ui.second->isEndTexture() == false)
				ui.second->Animate(0.5f);
		}
		else
		{
			ui.second->Stay();
		}
	}

	if (displaySetting == true)
	{
		for (auto ui : settingBoard.childUI)
		{
			if (ui.first == L"BACK")
			{
				if (ui.second->isCursorOn(_hWnd))
				{
					if (ui.second->isEndTexture() == false)
						ui.second->Animate(0.5f);
				}
				else
				{
					ui.second->Stay();
				}
			}

			if (ui.first == L"BGM")
			{
				if (isBgmOn)
				{
					ui.second->SetSprite(L"BGM_ON");

				}
				else
				{
					ui.second->SetSprite(L"BGM_OFF");

				}
			}
			if (ui.first == L"SFX")
			{
				if (isSfxOn)
				{
					ui.second->SetSprite(L"SFX_ON");
				}
				else
				{
					ui.second->SetSprite(L"SFX_OFF");
				}
			}
			
		}
	}

	if (displayControl == true)
	{
		for (auto ui : controlBoard.childUI)
		{
			if (ui.second->isCursorOn(_hWnd))
			{
				if (ui.second->isEndTexture() == false)
					ui.second->Animate(0.5f);
			}
			else
			{
				ui.second->Stay();
			}

		}
	}
}

void UIMgr::Render()
{
	menuBoard.Frame();
	menuBoard.Render();

	for (auto ui : menuBoard.childUI)
	{
		ui.second->Frame();
		ui.second->Render();
	}

	if (displaySetting == true)
	{
		settingBoard.Frame();
		settingBoard.Render();
		
		for (auto ui : settingBoard.childUI)
		{
			ui.second->Frame();
			ui.second->Render();
		}
	}

	if (displayControl == true)
	{
		controlBoard.Frame();
		controlBoard.Render();

		for (auto ui : controlBoard.childUI)
		{
			ui.second->Frame();
			ui.second->Render();
		}
	}
}

bool UIMgr::Release()
{
	return false;
}
