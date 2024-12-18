#include "DxLib.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define CAMERA_NEAR_CLIP 0.01f
#define CAMERA_FAR_CLIP 1000.0f

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// カメラのニアクリップとファークリップを設定
	SetCameraNearFar(0.01f, 1000.0f);

	// カメラの位置と注視点と上向きベクトルを格納する変数
	VECTOR cameraPos = VGet(0.0f, 0.0f, -5.0f);
	VECTOR cameraTarget = VGet(0.0f, 0.0f, 0.0f);
	VECTOR cameraUpVec = VGet(0.0f, 1.0f, 0.0f);

	// 3Dモデルをロードする
	int modelHandle = MV1LoadModel("Resource/Player/Player.x");

	// モデルの座標、回転、スケール値を格納する変数
	VECTOR modelPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR modelRot = VGet(0.0f, 0.0f, 0.0f);
	VECTOR modelScale = VGet(1.0f, 1.0f, 1.0f);

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		// カメラを配置する
		// 引数にはカメラの位置と注視点を渡す
		SetCameraPositionAndTargetAndUpVec(cameraPos, cameraTarget, cameraUpVec);

		// 3Dモデルの座標を設定する
		MV1SetPosition(modelHandle, modelPos);
		// 3Dモデルの回転値を設定する
		MV1SetRotationXYZ(modelHandle, modelRot);
		// 3Dモデルのスケールを設定する
		MV1SetScale(modelHandle, modelScale);

		// 3Dモデルを描画する
		MV1DrawModel(modelHandle);

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}

	// モデルをメモリから削除
	MV1DeleteModel(modelHandle);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
