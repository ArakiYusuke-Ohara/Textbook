#include "DxLib.h"
#include "TestScene.h"
#include "../Scene/SceneManager.h"
#include "../Input/Input.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParam.h"

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
	SetCameraNearFar(0.1f, 100.0f);
	SetCameraPositionAndTargetAndUpVec(VGet(10.0f, 0.0f, -30.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 1.0f, 0.0f));

	// Zバッファーを有効にする
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// Effekseerを初期化する
	EffekseerManager::GetInstance()->Init();

}

void TestScene::Load()
{
	// Effekseerデータをロード
	EffekseerManager::GetInstance()->Load();
}

void TestScene::Start()
{
	EffekseerManager::GetInstance()->Start();
}

void TestScene::Step()
{
	// Effekseerステップ
	EffekseerManager::GetInstance()->Step();

	// マウス座標を3D座標にする
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	VECTOR mousePos2D = { (float)mouseX, (float)mouseY, 0.995f };
	VECTOR mousePos3D = ConvScreenPosToWorldPos(mousePos2D);

	// Aキーでマウスの位置にEffectAを再生
	if (Input::IsTriggerKey(KEY_A))
	{
		EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_HIT, mousePos3D);
	}
	// Sキーでマウスの位置にEffectBを再生
	if (Input::IsTriggerKey(KEY_S))
	{
		EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_FIRE, mousePos3D);
	}
	// Dキーでマウスの位置にEffectCを再生
	if (Input::IsTriggerKey(KEY_D))
	{
		EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_RING, mousePos3D);
	}

	// 1キーでタイトルシーンへ
	if (Input::IsTriggerKey(KEY_1))
	{
		SceneManager::GetInstance()->ChangeScene(TITLE);
	}
}

void TestScene::Update()
{
	// Effekseer更新
	EffekseerManager::GetInstance()->Update();
}

void TestScene::Draw()
{
	// Effekseer描画
	EffekseerManager::GetInstance()->Draw();
}

void TestScene::Fin()
{
	// Zバッファーは非常に重いので、
	// 必要な時だけONにしておきたい

	// Zバッファーを無効にする
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	// Effekseer終了
	// EffekseerManager::GetInstance()->Fin();
}
