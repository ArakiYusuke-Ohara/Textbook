#include "DxLib.h"
#include "GameObject/Transform.h"
#include "Quatrenion/Quatrenion.h"
#include "MyMath/MyMath.h"

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
	VECTOR cameraPos = VGet(0.0f, 5.0f, -10.0f);
	VECTOR cameraTarget = VGet(0.0f, 1.0f, 0.0f);
	VECTOR cameraUpVec = VGet(0.0f, 1.0f, 0.0f);

	// 3Dモデルをロードする
	int modelHandle = MV1LoadModel("Data/Player/Player.x");

	// モデルの座標、回転、スケール値を格納する変数
	Transform transform = {};
	transform.position_3D = VGet(0.0f, 0.0f, 0.0f);
	transform.rotation = MyQuaternion::QIdentity();
	transform.scale = VGet(1.0f, 1.0f, 1.0f);

	Quaternion q = MyQuaternion::QfromAxisAngle(VGet(0.0f, 0.0f, 1.0f), 0.0f);
	MyQuaternion::QRotatation(transform.rotation, q);

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		// カメラを配置する
		// 引数にはカメラの位置と注視点を渡す
		SetCameraPositionAndTargetAndUpVec(cameraPos, cameraTarget, cameraUpVec);

		VECTOR cameraForward = MyMath::VecCreate(cameraPos, cameraTarget);
		cameraForward = MyMath::VecNormalize(cameraForward);
		VECTOR cameraRight = MyMath::VecCross3D(VGet(0.0f, 1.0f, 0.0f), cameraForward);
		MATRIX rMat = MyQuaternion::QToMatrix(transform.rotation);
		cameraForward = MyMath::MatTransform(rMat, cameraForward);
		cameraRight = MyMath::MatTransform(rMat, cameraRight);

		VECTOR move = {};
		if (CheckHitKey(KEY_INPUT_UP))
		{
			move = cameraForward;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			move = MyMath::VecScale(cameraForward, -1.0f);
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			move = MyMath::VecScale(cameraRight, -1.0f);
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			move = cameraRight;
		}

		move.y = 0.0f;
		move = MyMath::VecNormalize(move);
		move = MyMath::VecScale(move, 0.1f);

		// move = MyMath::MatTransform(rMat, move);
		transform.position_3D = MyMath::VecAdd(transform.position_3D, move);

		// スケール行列
		MATRIX scaleMat = MyMath::MatScale(transform.scale);
		// 回転行列
		MATRIX rotMat = MyQuaternion::QToMatrix(transform.rotation);
		// 平行移動行列
		MATRIX transMat = MyMath::MatTranslation(transform.position_3D);

		// 行列を合成
		MATRIX worldMat = MyMath::MatMult(transMat, rotMat);
		worldMat = MyMath::MatMult(worldMat, scaleMat);
		worldMat = MyMath::MatTransposition(worldMat);

		MV1SetMatrix(modelHandle, worldMat);

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
