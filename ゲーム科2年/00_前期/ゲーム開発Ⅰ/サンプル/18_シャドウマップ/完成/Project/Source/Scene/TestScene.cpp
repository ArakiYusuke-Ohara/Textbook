#include "DxLib.h"
#include "TestScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../Player/PlayerManager.h"
#include "../Floor/Floor.h"
#include "../ShadowMap/ShadowMap.h"

Floor* g_Floor = nullptr;

TestScene::TestScene() : SceneBase()
{
}

TestScene::~TestScene()
{
	Fin();
}

void TestScene::Init()
{
	// 適当にカメラを設定
	SetCameraNearFar(0.1f, 1000.0f);
	SetCameraPositionAndTargetAndUpVec(VGet(0.0f, 20.0f, -30.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));

	// プレイヤー
	PlayerManager::CreateInstance();
	PlayerManager::GetInstance()->CreatePlayer();
	PlayerManager::GetInstance()->Init();

	// 床
	g_Floor = new Floor;
	g_Floor->Init();

	// シャドウマップを生成
	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();
}

void TestScene::Load()
{
	PlayerManager::GetInstance()->Load();
	g_Floor->Load();
}

void TestScene::Start()
{
	PlayerManager::GetInstance()->Start();
	g_Floor->Start();
}

void TestScene::Step()
{
	g_Floor->Step();
	PlayerManager::GetInstance()->Step();

	// 1キーでタイトルシーンへ
	if (Input::IsTriggerKey(Input::KEY_1))
	{
		SceneManager::GetInstance()->ChangeScene(TITLE);
	}
}

void TestScene::Update()
{
	g_Floor->Update();
	PlayerManager::GetInstance()->Update();
}

void TestScene::Draw()
{
	// プレイヤーの影をシャドウマップに描画する
	ShadowMap::GetInstance()->StartDrawShadowMap();
	PlayerManager::GetInstance()->Draw();
	ShadowMap::GetInstance()->EndDrawShadowMap();

	// シャドウマップに描画された影を床に映しこむ
	ShadowMap::GetInstance()->StartAppearsShadowMap();
	g_Floor->Draw();
	ShadowMap::GetInstance()->EndAppearsShadowMap();

	// プレイヤーを通常描画
	PlayerManager::GetInstance()->Draw();
}

void TestScene::Fin()
{
	// Zバッファーは非常に重いので、
	// 必要な時だけONにしておきたい

	// Zバッファーを無効にする
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	// プレイヤー終了
	PlayerManager::GetInstance()->Fin();

	// 床削除
	delete g_Floor;

	// シャドウマップ削除
	ShadowMap::DeleteInstance();
}
