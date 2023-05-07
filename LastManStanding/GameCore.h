#pragma once
#include <Core.h>
#include "Window.h"
#include "DX11App.h"
#include "InputMgr.h"
#include "WriteMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"
#include "UIMgr.h"

#include "Background.h"
#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "PlayerBullet.h"
#include "DeadBody.h"

#pragma comment(lib, "DX11Engine_Library.lib")
#if _DEBUG
#pragma comment(lib, "DirectXTK_D.lib")
#else
#pragma comment(lib, "DirectXTK_R.lib")
#endif

class GameCore : public Core
{

	SINGLETON(GameCore);
private:
	GameCore() {}
	~GameCore() {}
private:
	Background background;
	World      world;
	Player     player;
	Enemy soldier;
	Enemy bommer;

	Collision bullet;
	Collision bomb;
	map<wstring, BaseObject*> extras;

	list<Enemy*> dynamicEnemyList;
	list<Collision*> dynamicHitboxList;

	PlayerBullet playerBullet;
	list<PlayerBullet*> playerBulletList;

	DeadBody deadBody;
	list<DeadBody*> deadBodyList;

	BaseObject Sacrificed;

	Text HUD;
	vector<Text*> dynamicTextList;

public:
	bool Init(HINSTANCE _hInstance, wstring _title, int _width, int _height);
	bool GameInit();

	bool InitBackground(wstring _fileName, int _sheets, wstring _fileType);
	bool InitWorld(wstring _fileName, int _sheets, wstring _fileType);
	bool InitPlayer();
	bool InitSoldier(wstring _fileName, int _sheets, wstring _fileType);
	bool InitBommer(wstring _fileName, int _sheets, wstring _fileType);

	bool InitBullet(wstring _fileName, int _sheets, wstring _fileType);
	bool InitBomb(wstring _fileName, int _sheets, wstring _fileType);
	bool AddExtras(const BaseObject& _extra, wstring _instanceName);

	bool InitEnemies();
	bool dynamicAddBommers(int _termSec);

	bool CheckWindowResized(RECT& _recent, RECT& _now);
	void ObjectUpdateByKey();
	void EnemyAI();

	void Dynamic_AddBullet(const Enemy& _enemy);
	void Dynamic_AddBomb(const Enemy& _enemy);

	bool InitPlayerBullet(wstring _fileName, int _sheets, wstring _fileType);
	void FirePLayerBullet();

	bool InitDeadBody(wstring _fileName, int _sheets, wstring _fileType);
	void AddDeadBody(const Enemy& _enemy);

	bool InitSacrificed(wstring _fileName, int _sheets, wstring _fileType);

	void AddText(Text* _Text);

	void Frame(bool& _RunGame);
	void Render();

	void GameRelease();
	void Release();

public:
	BaseObject OpeningScene;
	BaseObject MainScene;
	Text IntroUI;

	bool InitOpening(wstring _fileName, int _sheets, wstring _fileType);
	bool InitMain(wstring _fileName, int _sheets, wstring _fileType);
	void RenderOpening(bool& _OpenGame, bool& _RunGame);

	BaseObject victoryTitle;
	set<float> timeRank;
	Text recordTime;
	Text timeDatas;
	void TimeToFile(float _time);
	void FileToTime();
};

