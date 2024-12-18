#include "DxLib.h"
#include "TestScene.h"
#include "../Scene/SceneManager.h"
#include "../Camera/CameraManager.h"
#include "../Bullet/BulletManager.h"
#include "../Player/PlayerManager.h"
#include "../Collision/CollisionManager.h"
#include "../Sky/SkyManager.h"
#include "../Ground/GroundManager.h"
#include "../Level/LevelManager.h"
#include "../Block/BlockManager.h"
#include "../ObjectMover/ObjectMoverManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Input/Input.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../BGObject/BGObjectManager.h"

TestScene::TestScene() : SceneBase()
{
}

TestScene::~TestScene()
{
	Fin();
}

void TestScene::Init()
{
	CollisionManager::CreateInstance();

	LevelManager::GetInstance()->SetSelectLevel(LEVEL_TEST);

	ObjectMoverManager::CreateInstance();

	BGObjectManager::CreateInstance();

	SkyManager::CreateInstance();
	SkyManager::GetInstance()->Init();

	GroundManager::CreateInstance();
	GroundManager::GetInstance()->Init();

	BlockManager::CreateInstance();
	BlockManager::GetInstance()->Init();

	CameraManager::CreateInstance();
	CameraManager::GetInstance()->CreateCamera(PLAY_CAMERA);
	CameraManager::GetInstance()->Init();

	BulletManager::CreateInstance();
	BulletManager::GetInstance()->Init();

	PlayerManager::CreateInstance();
	PlayerManager::GetInstance()->CreatePlayer();
	PlayerManager::GetInstance()->Init();

	EnemyManager::CreateInstance();
	EnemyManager::GetInstance()->Init();

	EffekseerManager::GetInstance()->Init();

	SetFogEnable(TRUE);
	SetFogColor(0, 0, 100);
	SetFogStartEnd(20.0f, 400.0f);

	// Zバッファーを有効にする
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

}

void TestScene::Load()
{
	BGObjectManager::GetInstance()->Load();
	SkyManager::GetInstance()->Load();
	GroundManager::GetInstance()->Load();
	BlockManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	BulletManager::GetInstance()->Load();
	PlayerManager::GetInstance()->Load();
	EnemyManager::GetInstance()->Load();
	EffekseerManager::GetInstance()->Load();
}

void TestScene::Start()
{
	EffekseerManager::GetInstance()->Start();
	SkyManager::GetInstance()->Start();
	GroundManager::GetInstance()->Start();
	BlockManager::GetInstance()->Start();
	CameraManager::GetInstance()->Start();
	PlayerManager::GetInstance()->Start();
	EnemyManager::GetInstance()->Start();
	BGObjectManager::GetInstance()->LocateRandom();
}

void TestScene::Step()
{
	SkyManager::GetInstance()->Step();
	GroundManager::GetInstance()->Step();
	PlayerManager::GetInstance()->Step();
	EnemyManager::GetInstance()->Step();
	BulletManager::GetInstance()->Step();
	BlockManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	EffekseerManager::GetInstance()->Step();

	// 1キーでタイトルシーンへ
	if (Input::IsTriggerKey(KEY_1))
	{
		SceneManager::GetInstance()->ChangeScene(TITLE);
	}
}

void TestScene::Update()
{
	BGObjectManager::GetInstance()->Update();
	SkyManager::GetInstance()->Update();
	GroundManager::GetInstance()->Update();
	PlayerManager::GetInstance()->Update();
	EnemyManager::GetInstance()->Update();
	BulletManager::GetInstance()->Update();
	BlockManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	EffekseerManager::GetInstance()->Update();

	CollisionManager::GetInstance()->CheckCollision();

	PlayerManager::GetInstance()->CheckHP();
	EnemyManager::GetInstance()->CheckHP();
}

void TestScene::Draw()
{
	BGObjectManager::GetInstance()->Draw();
	BlockManager::GetInstance()->Draw();
	SkyManager::GetInstance()->Draw();
	GroundManager::GetInstance()->Draw();
	BlockManager::GetInstance()->Draw();
	EnemyManager::GetInstance()->Draw();
	PlayerManager::GetInstance()->Draw();
	BulletManager::GetInstance()->Draw();
	CameraManager::GetInstance()->Draw();
	CollisionManager::GetInstance()->Draw();
	EffekseerManager::GetInstance()->Draw();
}

void TestScene::Fin()
{
	// Zバッファーは非常に重いので、
	// 必要な時だけONにしておきたい

	// Zバッファーを無効にする
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	SetFogEnable(FALSE);

	BGObjectManager::DeleteInstance();
	SkyManager::DeleteInstance();
	GroundManager::DeleteInstance();
	BlockManager::DeleteInstance();
	BulletManager::DeleteInstance();
	PlayerManager::DeleteInstance();
	EnemyManager::DeleteInstance();
	CameraManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	EffekseerManager::GetInstance()->Fin();
	ObjectMoverManager::DeleteInstance();
}
