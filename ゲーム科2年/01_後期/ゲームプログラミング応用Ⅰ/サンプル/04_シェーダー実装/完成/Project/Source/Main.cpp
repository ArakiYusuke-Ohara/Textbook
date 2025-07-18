#include "DxLib.h"
#include "Input/Input.h"
#include "Camera/DebugCamera.h"
#include "Shader/ShaderManager.h"

// グローバル変数
int g_SphereHandle = 0;
int g_CubeHandle = 0;
DebugCamera g_DebugCamera = {};


// 初期化関数
// 始まる前に1回しか呼ばれない
void GameInit()
{
	// オリジナルシェーダーを使うように設定
	MV1SetUseOrigShader(TRUE);

	// シェーダー管理を生成
	ShaderManager::CreateInstance();

	// カメラ設定
	g_DebugCamera.Init();

	// 入力初期化
	Input::Init();
}

// ロード関数
void GameLoad()
{
	// シェーダーをロード
	ShaderManager::GetInstance()->Load();

	// 画像をロード
	g_SphereHandle = MV1LoadModel("Data/Model/Sphere.x");
	g_CubeHandle = MV1LoadModel("Data/Model/Cube.x");
}

// ステップ関数
void GameStep()
{
	// カメラステップ
	g_DebugCamera.Step();
}

// 更新関数
// ゲームが動いている間ずっと呼ばれる
void GameUpdate()
{
	Input::Update();

	// カメラ更新
	g_DebugCamera.Update();

	MV1SetPosition(g_SphereHandle, VGet(2.0f, 0.0f, 0.0f));
	MV1SetPosition(g_CubeHandle, VGet(-2.0f, 0.0f, 0.0f));
}

// 描画関数
// 画面に描画する
void GameDraw()
{
	// シェーダーを設定
	ShaderManager::GetInstance()->SetShader(NORMALMESH_NOLIGHT);

	// モデル描画
	MV1DrawModel(g_SphereHandle);
	MV1DrawModel(g_CubeHandle);

	// カメラ描画
	g_DebugCamera.Draw();
}

// 終了関数
// ゲーム終了時に1回だけ呼ばれる
void GameFin()
{
	// シェーダー終了
	ShaderManager::DeleteInstance();
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(1600, 900, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 初期化処理
	GameInit();

	// ロード処理
	GameLoad();

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		// 更新処理
		GameStep();
		GameUpdate();

		// 描画処理
		GameDraw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}

	// 終了処理
	GameFin();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
