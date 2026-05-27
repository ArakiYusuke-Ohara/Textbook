#include "DxLib.h"
#include "Input/Input.h"
#include "Network/Host.h"

enum MainState
{
	MAIN_STATE_NONE,
	MAIN_STATE_SELECT_MODE,
	MAIN_STATE_SET_IP,
	MAIN_STATE_CHAT
};

// クライアント用グローバル変数
Client* g_Client = nullptr;
MainState g_State = MAIN_STATE_SELECT_MODE;

// 関数のプロトタイプ宣言
void Update();			// 更新
void Draw();			// 描画
void UpdateSelectMode();// モード選択
void SetIP();			// IPアドレス設定


// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(1600, 900, 32);

	// 多重起動を許可する
	SetDoubleStartValidFlag(TRUE);

	// バックグラウンドでも動作し続ける
	SetAlwaysRunFlag(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ウィンドウサイズ設定
	SetWindowSize(1600, 900);

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 入力初期化
	Input::Init();

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		Sleep(1);

		// 画面をクリア
		ClearDrawScreen();

		// 入力更新
		Input::Update();

		// 更新
		Update();

		// 描画
		Draw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}

	// 入力終了
	Input::Fin();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

void Update()
{
	switch (g_State)
	{
		case MAIN_STATE_SELECT_MODE:
			UpdateSelectMode();
			break;

		case MAIN_STATE_SET_IP:
			SetIP();
			break;

		case MAIN_STATE_CHAT:
			g_Client->Update();
			break;

	}
}

void Draw()
{
	switch (g_State)
	{
	case MAIN_STATE_SELECT_MODE:
		DrawString(0, 0, "Hキー: ホスト / Cキー: クライアント", GetColor(255, 255, 255));
		break;

	case MAIN_STATE_CHAT:
		g_Client->Draw();
		break;

	}

}

void UpdateSelectMode()
{
	bool isInput = false;

	// Hキーでホストを生成
	if (Input::IsTriggerKey(KEY_H))
	{
		g_Client = new Host();
		g_Client->Init();
		isInput = true;
	}
	// Cキーでホストを生成
	if (Input::IsTriggerKey(KEY_C))
	{
		// クライアントを生成
		g_Client = new Client();
		g_Client->Init();
		isInput = true;
	}

	if (isInput)
	{
		// IPアドレス設定へ
		g_State = MAIN_STATE_SET_IP;
	}
}

void SetIP()
{
	if (!g_Client) return;

	// IPアドレスを設定
	IPDATA ipData;
	ipData.d1 = 10;
	ipData.d2 = 50;
	ipData.d3 = 174;
	ipData.d4 = 6;
	g_Client->SetIPAddress(ipData);

	// チャットへ
	g_State = MAIN_STATE_CHAT;
}
