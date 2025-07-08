#include "DxLib.h"

// グローバル変数
int g_VSHandle = 0;
int g_PSHandle = 0;
int g_SphereHandle = 0;
int g_CubeHandle = 0;
VECTOR g_CameraPos = {};
VECTOR g_CameraTarget = {};

// 初期化関数
// 始まる前に1回しか呼ばれない
void GameInit()
{
	// シェーダーをロード
	g_VSHandle = LoadVertexShader("Data/Shader/NormalMesh_DirLight_VS.vso");
	g_PSHandle = LoadPixelShader("Data/Shader/NormalMesh_DirLight_PS.pso");
	// 画像をロード
	g_SphereHandle = MV1LoadModel("Data/Model/Sphere.x");
	g_CubeHandle = MV1LoadModel("Data/Model/Cube.x");

	// カメラ設定
	SetCameraNearFar(0.1f, 1000.0f);
	g_CameraPos = VGet(0.0f, 0.0f, -10.0f);
	g_CameraTarget = VGet(0.0f, 0.0f, 0.0f);

	// シェーダーを有効にする
	int isValidShader = GetValidShaderVersion();
	MV1SetUseOrigShader(TRUE);
	SetUseVertexShader(g_VSHandle);
	SetUsePixelShader(g_PSHandle);
}

// 更新関数
// ゲームが動いている間ずっと呼ばれる
void GameUpdate()
{
	MV1SetPosition(g_SphereHandle, VGet(0.0f, 0.0f, 0.0f));
	MV1SetPosition(g_CubeHandle, VGet(0.0f, 0.0f, 0.0f));
	SetCameraPositionAndTargetAndUpVec(g_CameraPos, g_CameraTarget, VGet(0.0f, 1.0f, 0.0f));
}

// 描画関数
// 画面に描画する
void GameDraw()
{
	MV1DrawModel(g_SphereHandle);
}

// 終了関数
// ゲーム終了時に1回だけ呼ばれる
void GameFin()
{
	// シェーダーを無効にする
	SetUseVertexShader(-1);
	SetUsePixelShader(-1);

	// シェーダーを削除する
	DeleteShader(g_VSHandle);
	DeleteShader(g_PSHandle);
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

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		// 更新処理
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
