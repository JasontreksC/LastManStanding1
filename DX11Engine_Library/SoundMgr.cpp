#include "pch.h"
#include "SoundMgr.h"

bool SoundMgr::Init()
{
	FMOD_RESULT fr = FMOD::System_Create(&fmod_System);
	if (fr != FMOD_OK)
	{
		MessageBox(nullptr, L"사운드 시스템 생성 실패", L"오류", 0);
		return false;
	}
	fr = fmod_System->init(32, FMOD_INIT_NORMAL, 0);
	if (fr != FMOD_OK)
	{
		MessageBox(nullptr, L"사운드 시스템 초기화 실패", L"오류", 0);
		return false;
	}
	BgmChannel->setVolume(0.5f);
	SfxChannel->setVolume(0.5f);

	return true;
}

void SoundMgr::Update()
{
	fmod_System->update();
}

bool SoundMgr::AddFmodSound(string _fileName, string _instanceName, FMOD_MODE _loopmode)
{
	FMOD::Sound* newSound;
	FMOD_RESULT fr = fmod_System->createSound(_fileName.c_str(), _loopmode, nullptr, &newSound);
	if (fr != FMOD_OK)
	{
		MessageBox(nullptr, L"사운드 추가 실패", L"오류", 0);
		return false;
	}
	soundList.insert(make_pair(_instanceName.c_str(), newSound));
	return true;
}

bool SoundMgr::PlayFmodSound(string _instanceName, string _channel)
{
	if (_channel == "BGM")
	{
		FMOD_RESULT fr = fmod_System->playSound(soundList.find(_instanceName.c_str())->second, nullptr, false, &BgmChannel);
		if (fr != FMOD_OK)
		{
			MessageBox(nullptr, L"사운드 재생 실패", L"오류", 0);
			return false;
		}
	}
	else if (_channel == "SFX")
	{
		FMOD_RESULT fr = fmod_System->playSound(soundList.find(_instanceName.c_str())->second, nullptr, false, &SfxChannel);
		if (fr != FMOD_OK)
		{
			MessageBox(nullptr, L"사운드 재생 실패", L"오류", 0);
			return false;
		}
	}


	return true;
}

void SoundMgr::StopFmodSound(string _instanceName)
{
	int channel;
	soundList.find(_instanceName.c_str())->second->getMusicNumChannels(&channel);
	soundList.find(_instanceName.c_str())->second->setMusicChannelVolume(channel, 0.0f);
}

void SoundMgr::ReplyFmodSound(string _instanceName)
{
	int channel;
	soundList.find(_instanceName.c_str())->second->getMusicNumChannels(&channel);
	soundList.find(_instanceName.c_str())->second->setMusicChannelVolume(channel, 0.5f);
}

void SoundMgr::Release()
{
	for (auto sound : soundList)
	{
		sound.second->release();
	}
	fmod_System->close();
}
