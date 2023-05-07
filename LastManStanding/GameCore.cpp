#include "pch.h"
#include "Window.h"
#include "DX11App.h"
#include "ShaderMgr.h"
#include "GameCore.h"
#include <fstream>

bool GameCore::InitBackground(wstring _fileName, int _sheets, wstring _fileType)
{
    // 배경 객체 생성
    if (background.Create(L"BasicShader.txt") == false)
        return false;


    // 배경 텍스쳐 로드
    background.MakeSprite(L"Background_Default", _fileName, _sheets, _fileType);

    return true;
}

bool GameCore::InitWorld(wstring _fileName, int _sheets, wstring _fileType)
{
    // 월드 객체 생성
    if (world.Create(L"BasicShader.txt") == false)
        return false;

    // 월드 텍스쳐 로드
    world.MakeSprite(L"World_Default", _fileName, _sheets, _fileType);

    return true;
}

bool GameCore::InitPlayer()
{
    // 플레이어 객체 생성
    if (player.Create(L"BasicShader.txt") == false)
        return false;

    // 플레이어 텍스쳐 로드
    player.MakeSprite(L"Player_Walk", L"../res/PLayer/Walk/Frame_", 8, L".png");
    player.MakeSprite(L"Player_Crawl", L"../res/PLayer/Crawl/Frame_", 10, L".png");
    player.MakeSprite(L"Player_Attack", L"../res/PLayer/Attack/Frame_", 6, L".png");
    player.MakeSprite(L"PlayerDie_Shot", L"../res/PlayerDie_Shot/Frame_", 9, L".png");
    player.MakeSprite(L"PlayerDie_Bomb", L"../res/PlayerDie_Bomb/Frame_", 1, L".png");

    return true;
}

bool GameCore::InitSoldier(wstring _fileName, int _sheets, wstring _fileType)
{
    // 적군 객체 생성
    if (soldier.Create(L"BasicShader.txt") == false)
        return false;

    // 적군 텍스쳐 로드
    soldier.MakeSprite(L"Soldier_Default", _fileName, _sheets, _fileType);
    soldier.MakeSprite(L"SoldierDie", L"../res/SoldierDie/Frame_", 5, L".png");
    soldier.enemyType = EnemyType::SOLDIER;

    return true;
}

bool GameCore::InitBommer(wstring _fileName, int _sheets, wstring _fileType)
{
    // 폭격기 객체 생성
    if (bommer.Create(L"BasicShader.txt") == false)
        return false;

    // 폭격기 텍스쳐 로드
    bommer.MakeSprite(L"Bommer_Default", _fileName, _sheets, _fileType);

    bommer.enemyType = EnemyType::BOMMER;

    return true;
}

bool GameCore::InitBullet(wstring _fileName, int _sheets, wstring _fileType)
{
    // 총알 객체 생성
    if (bullet.Create(L"BasicShader.txt") == false)
        return false;

    // 총알 텍스쳐 로드
    bullet.MakeSprite(L"Bullet_Default", _fileName, _sheets, _fileType);

    bullet.hitboxType = HitboxType::BULLET;

    return true;
}

bool GameCore::InitBomb(wstring _fileName, int _sheets, wstring _fileType)
{
    // 폭탄 객체 생성
    if (bomb.Create(L"BasicShader.txt") == false)
        return false;

    // 폭탄 텍스쳐 로드
    bomb.MakeSprite(L"Bomb_Default", _fileName, _sheets, _fileType);

    bomb.hitboxType = HitboxType::BOMB;

    return true;
}

bool GameCore::AddExtras(const BaseObject& _extra, wstring _instanceName)
{
    BaseObject* newExtra = new BaseObject;
    *newExtra = _extra;
    extras.insert(make_pair(_instanceName.c_str(), newExtra));

    return true;
}

bool GameCore::InitEnemies()
{
    Enemy* newSoldier1 = new Enemy;
    *newSoldier1 = soldier;
    newSoldier1->SetPos_InWorld(1400.f, 460.f);
    dynamicEnemyList.push_back(newSoldier1);

    Enemy* newSoldier2 = new Enemy;
    *newSoldier2 = soldier;
    newSoldier2->SetPos_InWorld(1500.f, 460.f);
    dynamicEnemyList.push_back(newSoldier2);

    Enemy* newSoldier3 = new Enemy;
    *newSoldier3 = soldier;
    newSoldier3->SetPos_InWorld(2000.f, 460.f);
    dynamicEnemyList.push_back(newSoldier3);

    Enemy* newSoldier4 = new Enemy;
    *newSoldier4 = soldier;
    newSoldier4->SetPos_InWorld(2200.f, 460.f);
    dynamicEnemyList.push_back(newSoldier4);

    Enemy* newSoldier5 = new Enemy;
    *newSoldier5 = soldier;
    newSoldier5->SetPos_InWorld(2400.f, 460.f);
    dynamicEnemyList.push_back(newSoldier5);

    Enemy* newSoldier6 = new Enemy;
    *newSoldier6 = soldier;
    newSoldier6->SetPos_InWorld(3000.f, 460.f);
    dynamicEnemyList.push_back(newSoldier6);

    Enemy* newSoldier7 = new Enemy;
    *newSoldier7 = soldier;
    newSoldier7->SetPos_InWorld(3200.f, 460.f);
    dynamicEnemyList.push_back(newSoldier7);

    Enemy* newSoldier8 = new Enemy;
    *newSoldier8 = soldier;
    newSoldier8->SetPos_InWorld(3400.f, 460.f);
    dynamicEnemyList.push_back(newSoldier8);

    Enemy* newSoldier9 = new Enemy;
    *newSoldier9 = soldier;
    newSoldier9->SetPos_InWorld(4000.f, 460.f);
    dynamicEnemyList.push_back(newSoldier9);

    Enemy* newSoldier10 = new Enemy;
    *newSoldier10 = soldier;
    newSoldier10->SetPos_InWorld(4200.f, 460.f);
    dynamicEnemyList.push_back(newSoldier10);

    Enemy* newSoldier11 = new Enemy;
    *newSoldier11 = soldier;
    newSoldier11->SetPos_InWorld(4400.f, 460.f);
    dynamicEnemyList.push_back(newSoldier11);

    //==============================================================================================
    return true;
}

bool GameCore::Init(HINSTANCE _hInstance, wstring _title, int _width, int _height)
{
    // 윈도우, DX 초기화
    if (window.init(_hInstance, _title, _width, _height) == false)
        return false;

    if (DXAPP_INSTANCE->Init(window.GetWndSize(), window.GetWndHandle()) == false)
        return false;

    // 매니저 초기화
    WriteMgr::GetInst()->Init();
    SoundMgr::GetInst()->Init();
    UIMgr::GetInst()->Init();

    IDXGISurface1* pBackBuffer;
    HRESULT hr = DXAPP_INSTANCE->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface1),
        (void**)&pBackBuffer);

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"백버퍼 불러오기 실패", L"오류", 0);
    }
    if (SUCCEEDED(hr))
        WriteMgr::GetInst()->Set(pBackBuffer);


    // HUD 초기화
    if (HUD.Init(L"고딕", 30, POINT{ 10, 10 }, L" ", { 1, 0, 0, 1 }) == false)
        return false;

    if (recordTime.Init(L"고딕", 30, POINT{ 450, 500 }, L" ", { 0, 0, 1, 1 }) == false)
        return false;

    if (timeDatas.Init(L"고딕", 30, POINT{ 800, 500 }, L" ", { 0, 0, 1, 1 }) == false)
        return false;

    // 오프닝 초기화
    if (InitOpening(L"../res/OpeningScene/Frame_", 179, L".png") == false)
        return false;

    if (InitMain(L"../res/MainScene/Frame_", 179, L".png") == false)
        return false;


    // 오브젝트 초기화

    if (InitBackground(L"../res/Background/Frame_", 179, L".png") == false)
        return false;

    if (InitWorld(L"../res/GameWorld/GameWorld", 1, L".png") == false)
        return false;

    if (InitPlayer() == false)
        return false;

    if (InitSoldier(L"../res/EnemySoldier/Frame_", 24, L".png") == false)
        return false;

    if (InitBommer(L"../res/EnemyBomber/Frame_", 28, L".png") == false)
        return false;

    if (InitBullet(L"../res/EnemyBullet", 1, L".png") == false)
        return false;

    if (InitBomb(L"../res/Explosion24/Frame_", 24, L".png") == false)
        return false;

    if (InitPlayerBullet(L"../res/PlayerBullet", 1, L".png") == false)
        return false;

    if (InitDeadBody(L"../res/Body/Body", 3, L".png") == false)
        return false;

    if (InitSacrificed(L"../res/Sacrificed/Frame_", 58, L".png") == false)
        return false;

    // 텍스쳐 크기 조정
    world.SetObjScale_ByTextureSize();

    player.SetObjScale_ByTextureSize();
    player.SetObjScale_ByManual(0.2f);

    soldier.SetObjScale_ByTextureSize();
    soldier.SetObjScale_ByManual(0.2f);



    bommer.SetObjScale_ByTextureSize();
    bommer.SetObjScale_ByManual(0.5f);



    bullet.SetObjScale_ByTextureSize();
    bullet.SetObjScale_ByManual(0.2f);

    bomb.SetObjScale_ByTextureSize();
    bullet.SetObjScale_ByManual(1.0f);

    playerBullet.SetObjScale_ByTextureSize();
    playerBullet.SetObjScale_ByManual(0.2f);

    deadBody.SetObjScale_ByTextureSize();
    deadBody.SetObjScale_ByManual(0.2f);

    // 사운드 초기화
    SoundMgr::GetInst()->AddFmodSound("../res/Sounds/Bomber.mp3", "Bomber", FMOD_LOOP_OFF);
    SoundMgr::GetInst()->AddFmodSound("../res/Sounds/ExplosionSound.mp3", "ExplosionSound", FMOD_LOOP_OFF);
    SoundMgr::GetInst()->AddFmodSound("../res/Sounds/GunShot.mp3", "GunShot", FMOD_LOOP_OFF);
    SoundMgr::GetInst()->AddFmodSound("../res/Sounds/PlayerGunfire.mp3", "PlayerGunfire", FMOD_LOOP_OFF);
    SoundMgr::GetInst()->AddFmodSound("../res/Sounds/BulletHit.mp3", "BulletHit", FMOD_LOOP_OFF);

    return true;
}

bool GameCore::GameInit()
{
    TimeMgr::GetInst()->Init();
    InputMgr::GetInst()->Init();

    // 텍스쳐 위치 조정
    world.SetWorldPos();
    player.SetPlayerPos();
    InitEnemies();

    BaseObject victoryFlag;
    victoryFlag.Create(L"BasicShader.txt");
    victoryFlag.MakeSprite(L"victoryFlag", L"../res/Flag/Frame_", 6, L".png");
    victoryFlag.SetObjScale_ByTextureSize();
    victoryFlag.SetObjScale_ByManual(0.5f);
    victoryFlag.SetPos_InWorld(7000.0f, 470.0f);
    AddExtras(victoryFlag, L"Flag");

    victoryTitle.Create(L"BasicShader.txt");
    victoryTitle.MakeSprite(L"victoryTitle", L"../res/Victory", 1, L".png");
    victoryTitle.SetObjScale_ByTextureSize();

    return true;
}

bool GameCore::CheckWindowResized(RECT& _recent, RECT& _now)
{
    if (_recent == _now)
        return true;
    else
    {
        _recent = _now;
        return false;
    }
}

void GameCore::ObjectUpdateByKey()
{
    DeadBody* playerBody = nullptr;
    for (auto body : deadBodyList)
    {
        if (body->BodyCarrying == true)
        {
            playerBody = body;
            break;
        }
    }

    if (player.playerLife <= 0 || player.isVictory == true)
        return;

    if (InputMgr::GetInst()->STATE.ATTACK == false)
    {
        if (InputMgr::GetInst()->STATE.MOVE_CRAWL == true)
        {
            player.PlayerState_Crawl();
        }
        if (InputMgr::GetInst()->STATE.MOVE_CRAWL == false)
        {
            player.PlayerState_Walk();
        }
    }


    if (InputMgr::GetInst()->STATE.MOVE_CRAWL == false)
    {
        if (playerBody != nullptr)
            playerBody->BodyState_Walk();
        if (InputMgr::GetInst()->STATE.MOVE_RIGHT)
        {
            if (player.isCenter() == true)
            {

                if (world.Move(0.5f, 0.0f) == false)
                    player.Move(0.5f, 0.0f);
                else
                {
                    for (auto enemy : dynamicEnemyList)
                    {
                        enemy->Move(0.5f, 0.0f);
                    }
                    for (auto body : deadBodyList)
                    {
                        body->Move(0.5f, 0.0f);
                    }
                    for (auto hits : dynamicHitboxList)
                    {
                        hits->Move(0.5f, 0.0f);
                    }
                    for (auto pb : playerBulletList)
                    {
                        pb->Move(0.5f, 0.0f);
                    }
                    extras.find(L"Flag")->second->Move(0.5f, 0.0f);
                }
            }
            else
                player.Move(0.5f, 0.0f);
            player.Reverse_L();
            if (playerBody != nullptr)
                playerBody->Reverse_L();
            player.Animate(0.5f);
        }
        if (InputMgr::GetInst()->STATE.MOVE_LEFT)
        {
            if (player.isCenter() == true)
            {

                if (world.Move(-0.5f, 0.0f) == false)
                    player.Move(-0.5f, 0.0f);
                else
                {
                    for (auto enemy : dynamicEnemyList)
                    {
                        enemy->Move(-0.5f, 0.0f);
                    }
                    for (auto body : deadBodyList)
                    {
                        body->Move(-0.5f, 0.0f);
                    }
                    for (auto hits : dynamicHitboxList)
                    {
                        hits->Move(-0.5f, 0.0f);
                    }
                    for (auto pb : playerBulletList)
                    {
                        pb->Move(-0.5f, 0.0f);
                    }
                    extras.find(L"Flag")->second->Move(-0.5f, 0.0f);
                }
            }

            else
                player.Move(-0.5f, 0.0f);
            player.Reverse_R();
            if (playerBody != nullptr)
                playerBody->Reverse_R();
            player.Animate(0.5f);
        }
    }
    if (InputMgr::GetInst()->STATE.MOVE_CRAWL)
    {
        if (playerBody != nullptr)
            playerBody->BodyState_Crawl();
        if (InputMgr::GetInst()->STATE.MOVE_RIGHT)
        {
            if (player.isCenter() == true)
            {

                if (world.Move(0.25f, 0.0f) == false)
                    player.Move(0.25f, 0.0f);
                else
                {
                    for (auto enemy : dynamicEnemyList)
                    {
                        enemy->Move(0.25f, 0.0f);
                    }
                    for (auto body : deadBodyList)
                    {
                        body->Move(0.25f, 0.0f);

                    }
                    for (auto hits : dynamicHitboxList)
                    {
                        hits->Move(0.25f, 0.0f);
                    }
                    for (auto pb : playerBulletList)
                    {
                        pb->Move(0.25f, 0.0f);
                    }
                    extras.find(L"Flag")->second->Move(0.25f, 0.0f);
                }
            }
            else
                player.Move(0.25f, 0.0f);
            player.Reverse_L();
            if (playerBody != nullptr)
                playerBody->Reverse_L();
            player.Animate(0.1f);
        }
        if (InputMgr::GetInst()->STATE.MOVE_LEFT)
        {
            if (player.isCenter() == true)
            {

                if (world.Move(-0.25f, 0.0f) == false)
                    player.Move(-0.25f, 0.0f);
                else
                {
                    for (auto enemy : dynamicEnemyList)
                    {
                        enemy->Move(-0.25f, 0.0f);
                    }
                    for (auto body : deadBodyList)
                    {
                        body->Move(-0.25f, 0.0f);
                    }
                    for (auto hits : dynamicHitboxList)
                    {
                        hits->Move(-0.25f, 0.0f);
                    }
                    for (auto pb : playerBulletList)
                    {
                        pb->Move(-0.25f, 0.0f);
                    }
                    extras.find(L"Flag")->second->Move(-0.25f, 0.0f);
                }
            }
            else
                player.Move(-0.25f, 0.0f);
            player.Reverse_R();
            if (playerBody != nullptr)
                playerBody->Reverse_R();
            player.Animate(0.1f);
        }
    }

    if (InputMgr::GetInst()->STATE.ATTACK)
    {
        player.PlayerState_Attack();
        int index = player.Animate(0.3);

        if (player.spriteIndex == 6.0f)
        {
            SoundMgr::GetInst()->PlayFmodSound("PlayerGunfire", "SFX");
            FirePLayerBullet();
        }

        if (player.isAttackFisish())
            InputMgr::GetInst()->STATE.ATTACK = false;
    }

    if (InputMgr::GetInst()->STATE.CARRY)
    {
        // 적 시체를 들고있는 상태면
        if (player.carryingBody == true)
        {
            // 적 시체를 내려놓음
            for (auto body : deadBodyList)
            {
                if (body->BodyCarrying == true)
                {
                    body->BodyState_Lay();
                    body->BodyCarrying = false;
                    player.carryingBody = false;
                    break;
                }
            }
        }
        // 적 시체를 들고있지 않다면
        else
        {
            for (auto body : deadBodyList)
            {
                // 근처에 적 시체가 있다면
                if (player.GetCenterPosX() >= body->GetLeftPosX() &&
                    player.GetCenterPosX() <= body->GetRightPosX())
                {
                    // 적 시체를 듦
                    body->BodyCarrying = true;
                    player.carryingBody = true;
                    break;
                }
            }
        }
        InputMgr::GetInst()->STATE.CARRY = false;
    }

}

void GameCore::EnemyAI()
{
    for (auto enemy : dynamicEnemyList)
    {
        if (enemy->enemyType == EnemyType::SOLDIER)
        {
            if (enemy->GetLeftPosX() - player.GetLeftPosX() <= 1.0f)
            {
                enemy->Animate(0.33f);
                if (enemy->isSpriteName(L"Soldier_Default") == true && enemy->spriteIndex == 6)
                {
                    Dynamic_AddBullet(*enemy);
                    SoundMgr::GetInst()->PlayFmodSound("GunShot", "SFX");
                }

            }
            else
            {
                enemy->Stay();
            }
        }

        if (enemy->enemyType == EnemyType::BOMMER)
        {
            static bool bommersound = true;
            enemy->Move(0.6f, 0.0f);
            if (enemy->GetLeftPosX() <= 1.5f && enemy->GetLeftPosX() >= 1.48f)
            {
                SoundMgr::GetInst()->PlayFmodSound("Bomber", "SFX");
                bommersound = false;
            }
            else if (enemy->GetLeftPosX() > 1.5f)
                bommersound = true;

            if (enemy->GetLeftPosX() <= 1.0f)
            {
                enemy->Animate(1.0f);
                if (enemy->spriteIndex == 27.0f)
                {
                    Dynamic_AddBomb(*enemy);
                    SoundMgr::GetInst()->PlayFmodSound("ExplosionSound", "SFX");
                }
            }

        }
    }
}

void GameCore::Dynamic_AddBullet(const Enemy& _enemy)
{

    Collision* newBullet = new Collision;
    *newBullet = bullet;
    newBullet->SetPosOnEnemy(_enemy);
    dynamicHitboxList.push_back(newBullet);
}

bool GameCore::dynamicAddBommers(int _termSec)
{
    static int temp = 0;

    if ((int)(TimeMgr::GetInst()->GetGametime()) % _termSec == 0)
    {
        temp++;
    }
    else if (temp > 0)
    {
        Enemy* newBommer = new Enemy;
        *newBommer = bommer;
        newBommer->SetPos_InWorld(7000.f, -100.f);
        dynamicEnemyList.push_back(newBommer);
        temp = 0;
    }
    return true;

}

void GameCore::Dynamic_AddBomb(const Enemy& _enemy)
{
    Collision* newBomb = new Collision;
    *newBomb = bomb;
    newBomb->SetPosOnEnemy(_enemy);
    dynamicHitboxList.push_back(newBomb);
}

bool GameCore::InitPlayerBullet(wstring _fileName, int _sheets, wstring _fileType)
{
    // 플레이어 객체 생성
    if (playerBullet.Create(L"BasicShader.txt") == false)
        return false;

    // 플레이어 텍스쳐 로드
    playerBullet.MakeSprite(L"PlayerBullet_Default", _fileName, _sheets, _fileType);

    return true;
}

void GameCore::FirePLayerBullet()
{
    PlayerBullet* newPlayerBullet = new PlayerBullet;
    *newPlayerBullet = playerBullet;
    newPlayerBullet->SetPositionOnPLayer(player);
    if (player.isHeadingRight() == false)
        newPlayerBullet->Reverse_R();
    else
        newPlayerBullet->Reverse_L();
    playerBulletList.push_back(newPlayerBullet);
}

bool GameCore::InitDeadBody(wstring _fileName, int _sheets, wstring _fileType)
{
    // 시체 객체 생성
    if (deadBody.Create(L"BasicShader.txt") == false)
        return false;

    // 시체 텍스쳐 로드
    deadBody.MakeSprite(L"DeadBody_Default", _fileName, _sheets, _fileType);

    return true;
}

void GameCore::AddDeadBody(const Enemy& _enemy)
{
    DeadBody* newDeadBody = new DeadBody;
    *newDeadBody = deadBody;
    newDeadBody->SetPosOnEnemy(_enemy);
    deadBodyList.push_back(newDeadBody);
}

bool GameCore::InitSacrificed(wstring _fileName, int _sheets, wstring _fileType)
{
    // 사망문구 객체 생성
    if (Sacrificed.Create(L"BasicShader.txt") == false)
        return false;

    // 사망문구 텍스쳐 로드
    Sacrificed.MakeSprite(L"Sacrificed_Default", _fileName, _sheets, _fileType);

    Sacrificed.SetObjScale_ByTextureSize();
    return true;
}

void GameCore::AddText(Text* _Text)
{
    Text* newText = new Text;
    *newText = *_Text;
    dynamicTextList.push_back(newText);
}

void GameCore::Frame(bool& _RunGame)
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    RECT recentRect;
    GetClientRect(window.GetWndHandle(), &recentRect);

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            TimeMgr::GetInst()->Update();           
            InputMgr::GetInst()->Update();

            if (UIMgr::GetInst()->isSfxOn)
            {
                SoundMgr::GetInst()->SfxChannel->setMute(false);
            }
            else
            {
                SoundMgr::GetInst()->SfxChannel->setMute(true);
            }

            SoundMgr::GetInst()->Update();
            // 배경 애니메이션
            background.Animate(0.4f);

            // HUD 기능
            wstring HUDtext = L"FPS : " + to_wstring(TimeMgr::GetInst()->GetFPS());

            // 일정 시간마다 폭격기 추가
            dynamicAddBommers(10);

            int iSoldier = 0;
            int iBommer = 0;
            for (auto soldier : dynamicEnemyList)
            {
                if (soldier->enemyType == EnemyType::SOLDIER)
                    ++iSoldier;
                else
                    ++iBommer;
            }
            HUDtext += L"  남은 적군: " + to_wstring(iSoldier);
            HUDtext += L"  남은 폭격기: " + to_wstring(iBommer);
            HUDtext += L"  시간 : " + to_wstring(TimeMgr::GetInst()->GetGametime());
            HUDtext += L"\nDT : " + to_wstring(TimeMgr::GetInst()->GetDeltaTime());

            if (InputMgr::GetInst()->STATE.HUD_ON)
                HUD.text = HUDtext;
            else
                HUD.text = L" ";

            // 화면 크기 변화에 따른 사이즈와 위치 재조정
            RECT nowRect;
            GetClientRect(window.GetWndHandle(), &nowRect);
            if (CheckWindowResized(recentRect, nowRect) == false)
            {
                world.SetObjSclae_Dynaic(window.GetWndHandle());
                player.SetObjSclae_Dynaic(window.GetWndHandle()); // 동적 사이즈 조정 후 위치 재설정
            }

            ObjectUpdateByKey(); // 키 입력에 의한 오브젝트 행동처리기
            EnemyAI(); // 적의 반응


            // 동적 히트박스 리스트의 동작
            for (auto hitbox : dynamicHitboxList)
            {
                if (hitbox->hitboxType == HitboxType::BULLET)
                {
                    hitbox->BulletMove(1.5f);
                }
                if (hitbox->hitboxType == HitboxType::BOMB)
                {
                    hitbox->Animate(0.3f);
                }
            }

            // 플레이어 총알 동작
            for (auto pb : playerBulletList)
            {
                if (pb->isHeadingRight())
                    pb->PlayerBullet_MoveR(1.5f);
                else
                    pb->PlayerBullet_MoveL(1.5f);
            }

            // 기타 오브젝트 동작
            for (auto extra : extras)
            {
                if (extra.first == L"Sacrificed" && extra.second->isEndTexture() == false)
                    extra.second->Animate(0.5f);
            }
            extras.find(L"Flag")->second->Animate(0.33);



            // 동적 리스트들의 요소들의 상태를 체크 후 삭제
            // 적
            for (auto iter = dynamicEnemyList.begin(); iter != dynamicEnemyList.end(); ++iter)
            {
                if ((*iter)->enemyType == EnemyType::SOLDIER)
                {
                    if ((*iter)->isSoldierDead() == true)
                    {
                        (*iter)->SetSprite(L"SoldierDie");
 
                        if ((*iter)->isEndTexture())
                        {
                            AddDeadBody(**iter);
                            delete (*iter);
                            dynamicEnemyList.erase(iter++);
                        }
                    }
                    else
                        (*iter)->SetSprite(L"Soldier_Default");
                }
                else if ((*iter)->enemyType == EnemyType::BOMMER)
                {
                    if ((*iter)->isBommerGone() == true)
                    {
                        delete (*iter);
                        dynamicEnemyList.erase(iter++);
                    }
                }
                if (iter == dynamicEnemyList.end())
                    break;
            }
            // 시체
            for (auto iter = deadBodyList.begin(); iter != deadBodyList.end(); ++iter)
            {
                if ((*iter)->BodyLife == false)
                {
                    delete (*iter);
                    deadBodyList.erase(iter++);
                }

                else
                {
                    if ((*iter)->BodyCarrying == true && player.carryingBody == true)
                    {
                        (*iter)->SetPosOnPLayer(player);
                    }
                }

                if (iter == deadBodyList.end())
                    break;
            }

            // 히트박스
            for (auto iter = dynamicHitboxList.begin(); iter != dynamicHitboxList.end(); ++iter)
            {
                if ((*iter)->hitboxType == HitboxType::BULLET)
                {
                    if ((*iter)->isBulletFinish() == true)
                    {
                        delete (*iter);
                        dynamicHitboxList.erase(iter++);
                    }
                    else
                    {
                        if ((*iter)->HitPlayer(player, player.isCrawling) == true)
                        {
                            if (player.playerLife == 0)
                            {
                                SoundMgr::GetInst()->PlayFmodSound("BulletHit", "SFX");
                                delete (*iter);
                                dynamicHitboxList.erase(iter++);
                                player.SetSprite(L"PlayerDie_Shot");
                            }
                        }
                    }
                }
                else if ((*iter)->hitboxType == HitboxType::BOMB)
                {
                    if ((*iter)->isBombFinish() == true)
                    {
                        delete (*iter);
                        dynamicHitboxList.erase(iter++);
                    }
                    else if ((*iter)->isBombFinish() == false)
                    {
                        for (auto body : deadBodyList)
                        {
                            if ((*iter)->GetLeftPosX() <= body->GetLeftPosX() &&
                                body->GetRightPosX() <= (*iter)->GetRightPosX())
                                if ((*iter)->spriteIndex > 70)
                                {
                                    body->BodyLife = false;
                                    if (player.GetLeftPosX() == body->GetLeftPosX() && player.carryingBody == true)
                                        player.carryingBody = false;
                                }
                        }
                        if ((*iter)->HitPlayer(player, player.isCrawling) == true)
                        {      
                            player.SetSprite(L"PlayerDie_Bomb");
                        }
                    }
                }
                if (iter == dynamicHitboxList.end())
                    break;
            }

            // 플레이어 총알
            for (auto iter = playerBulletList.begin(); iter != playerBulletList.end(); ++iter)
            {
                if ((*iter)->isPlayerBullet_Finish() == true)
                {
                    delete (*iter);
                    playerBulletList.erase(iter++);
                }

                else if ((*iter)->isPlayerBullet_Finish() == false)
                {
                    for (auto enemy : dynamicEnemyList)
                    {
                        if ((player.GetCenterPosX() < enemy->GetLeftPosX() && (*iter)->isHeadingRight() == true  && (*iter)->GetRightPosX() >= enemy->GetLeftPosX()) ||
                            (player.GetCenterPosX() > enemy->GetLeftPosX() && (*iter)->isHeadingRight() == false && (*iter)->GetLeftPosX() <= enemy->GetRightPosX()))
                            if (enemy->enemyType == EnemyType::SOLDIER)
                            {
                                SoundMgr::GetInst()->PlayFmodSound("BulletHit", "SFX");
                                enemy->SoldierLife = false;
                                delete (*iter);
                                playerBulletList.erase(iter++);
                                break;
                            }
                    }
                }

                if (iter == playerBulletList.end())
                {
                    break;
                }
            }

            if (player.playerLife <= 0)
            {
                if (player.isEndTexture() == false)
                {
                    player.Animate(0.3f);
                }
                if (extras.find(L"Sacrificed") == extras.end())
                {
                    AddExtras(Sacrificed, L"Sacrificed");
                }

                if (GetAsyncKeyState(0x52) & 0x8000)
                {
                    break;
                }
            }
            if (player.GetCenterPosX() >= extras.find(L"Flag")->second->GetLeftPosX() && player.GetCenterPosX() <= extras.find(L"Flag")->second->GetRightPosX())
            {
                player.isVictory = true;
                static int i = 1;
                if (i)
                {
                    AddExtras(victoryTitle, L"victoryTitle");

                    float record = TimeMgr::GetInst()->GetGametime();
                    recordTime.text = L"Your Record : \n" + to_wstring(record);
                    AddText(&recordTime);

                    timeRank.insert(record);
                    FileToTime();

                    wstring rankStr = L"Best Records\n";
                    auto time = timeRank.begin();
                    for (int j = 0; j < timeRank.size() && j < 5; j++)
                    {
                        TimeToFile(*time);
                        rankStr += to_wstring(j + 1) + L". " + to_wstring(*time++) + L"\n";
                    }

                    timeDatas.text = rankStr;
                    AddText(&timeDatas);
                    --i;

                }
                if (GetAsyncKeyState(0x52) & 0x8000)
                {
                    i = 1;
                    break;
                }
            }

            

            Render();
        }
    }
    if (msg.message == WM_QUIT)
        _RunGame = false;
}

void GameCore::Render()
{
    DXAPP_INSTANCE->Clear();

    background.Frame();
    background.Render();

    world.Frame();
    world.Render();

    player.Frame();
    player.Render();
    for (auto enemy : dynamicEnemyList)
    {
        enemy->Frame();
        enemy->Render();
    }

    for (auto body : deadBodyList)
    {
        body->Frame();
        body->Render();
    }

    for (auto hitbox : dynamicHitboxList)
    {
        hitbox->Frame();
        hitbox->Render();
    }

    for (auto pb : playerBulletList)
    {
        pb->Frame();
        pb->Render();
    }

    for (auto extra : extras)
    {
        extra.second->Frame();
        extra.second->Render();
    }
    timeRank.clear();

    WriteMgr::GetInst()->Render(dynamicTextList);
    WriteMgr::GetInst()->Draw(HUD);
    DXAPP_INSTANCE->Render();
}

void GameCore::GameRelease()
{
    for (auto pb : playerBulletList)
    {
        delete pb;
    }
    playerBulletList.clear();

    for (auto hitbox : dynamicHitboxList)
    {
        delete hitbox;
    }
    dynamicHitboxList.clear();

    for (auto extra : extras)
    {
        delete extra.second;
    }
    extras.clear();

    for (auto enemy : dynamicEnemyList)
    {
        delete enemy;
    }
    dynamicEnemyList.clear();


    for (auto deadBody : deadBodyList)
    {
        delete deadBody;
    }
    deadBodyList.clear();

    for (auto text : dynamicTextList)
    {
        delete text;
    }
    dynamicTextList.clear();

    player.playerLife = 1;
    player.carryingBody = false;
    player.isVictory = false;
}

void GameCore::Release()
{
}

bool GameCore::InitOpening(wstring _fileName, int _sheets, wstring _fileType)
{
    // 오프닝씬 객체 생성
    if (OpeningScene.Create(L"BasicShader.txt") == false)
        return false;

    // 오프닝씬 텍스쳐 로드
    OpeningScene.MakeSprite(L"Opening_Default", _fileName, _sheets, _fileType);

    return true;
}

bool GameCore::InitMain(wstring _fileName, int _sheets, wstring _fileType)
{
    // 메인씬 객체 생성
    if (MainScene.Create(L"BasicShader.txt") == false)
        return false;

    // 메인씬 텍스쳐 로드
    MainScene.MakeSprite(L"Main_Default", _fileName, _sheets, _fileType);
        
    return true;
}

void GameCore::RenderOpening(bool& _OpenGame, bool& _RunGame)
{
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            DXAPP_INSTANCE->Clear();
            UIMgr::GetInst()->Update(window.GetWndHandle());

            if (OpeningScene.isEndTexture() == false)
            {
                OpeningScene.Animate(0.4f);
                OpeningScene.Frame();
                OpeningScene.Render();
            }
            else
            {
                for (auto button : UIMgr::GetInst()->menuBoard.childUI)
                {
  
                    if (button.second->isCursorOn(window.GetWndHandle()) == true)
                    {
                        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
                        {
                            if (button.first == L"PLAY")
                            {
                                _OpenGame = false;
                                _RunGame = true;
                            }
                            else if (button.first == L"QUIT")
                            {
                                _OpenGame = false;
                                _RunGame = false;
                            }
                            else if (button.first == L"SETTINGS")
                            {
                                UIMgr::GetInst()->displaySetting = true;


                                if (UIMgr::GetInst()->displayControl == true)
                                    UIMgr::GetInst()->displayControl = false;

                            }
                            else if (button.first == L"CONTROL")
                            {
                                UIMgr::GetInst()->displayControl = true;


                                if (UIMgr::GetInst()->displaySetting == true)
                                    UIMgr::GetInst()->displaySetting = false;
                            }                            
                        }
                    }                    
                }

                for (auto button : UIMgr::GetInst()->settingBoard.childUI)
                {
                    if (UIMgr::GetInst()->displaySetting == true)
                    {
                        if (button.second->isCursorOn(window.GetWndHandle()) == true)
                        {
                            static int k = 0;
                            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
                            {
                                if (button.first == L"BACK")
                                {
                                    UIMgr::GetInst()->displaySetting = false;
                                }
                                else if (button.first == L"BGM")
                                {
                                    if (k == 0)
                                    {
                                        UIMgr::GetInst()->isBgmOn = !(UIMgr::GetInst()->isBgmOn);
                                        k = 1;
                                    }
                                }
                                else if (button.first == L"SFX")
                                {
                                    if (k == 0)
                                    {
                                        UIMgr::GetInst()->isSfxOn = !(UIMgr::GetInst()->isSfxOn);
                                        k = 1;
                                    }
                                }
                            }
                            else if (GetAsyncKeyState(VK_LBUTTON) == 0 && k == 1)
                                k = 0;
                        }
                    }
                }
                for (auto button : UIMgr::GetInst()->controlBoard.childUI)
                {
                    if (UIMgr::GetInst()->displayControl == true)
                    {
                        if (button.second->isCursorOn(window.GetWndHandle()) == true)
                        {
                            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
                            {
                                if (button.first == L"Close")
                                {
                                    UIMgr::GetInst()->displayControl = false;
                                }
                            }
                        }
                    }
                }
                
                if (UIMgr::GetInst()->isBgmOn)
                {
                    SoundMgr::GetInst()->BgmChannel->setMute(false);
                }
                else
                {
                    SoundMgr::GetInst()->BgmChannel->setMute(true);
                }

                MainScene.Animate(0.4f);
                MainScene.Frame();
                MainScene.Render();

                UIMgr::GetInst()->Render();
            }

            DXAPP_INSTANCE->Render();
            if (_OpenGame == false)
                break;
        }
    }
    if (msg.message == WM_QUIT)
    {
        _OpenGame = false;
        _RunGame = false;
    }
}



void GameCore::TimeToFile(float _time)
{
    ofstream ofs("timeRank.txt", ios::app);
    ofs << _time << endl;
    ofs.close();
}

void GameCore::FileToTime()
{
    ifstream ifs("timeRank.txt");

    if (ifs.fail())
        return;

    float buffer;
    while (ifs.eof() == false)
    {
        ifs >> buffer;
        timeRank.insert(buffer);
    }
    ifs.close();
}

