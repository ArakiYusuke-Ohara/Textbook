#include "DxLib.h"
#include "Network/NetworkManager.h"

// 関数のプロトタイプ宣言
void Update();
void Draw();
void UpdateOffline();
void UpdateOnline();
void DrawOffline();
void DrawOnline();

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

	// ウィンドウサイズ設定
	SetWindowSize(1600, 900);

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// ネットワークマネージャー生成
	NetworkManager::CreateInstance();

	// IPアドレスを設定
	IPDATA ipData;
	ipData.d1 = 113;
	ipData.d2 = 42;
	ipData.d3 = 77;
	ipData.d4 = 130;

	// IPアドレス設定
	NetworkManager::GetInstance()->SetIPAddress(ipData);

	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		// 画面をクリア
		ClearDrawScreen();

		// 更新
		Update();

		// 描画
		Draw();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// 画面フリップ
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

void Update()
{
	NetworkGameState state = NetworkManager::GetInstance()->GetNetworkGameState();
	switch (state)
	{
	case GAME_STATE_OFFLINE: UpdateOffline(); break;
	case GAME_STATE_ONLINE: UpdateOnline(); break;
	}

	// ネットワークマネージャー更新
	NetworkManager::GetInstance()->Update();

}

void UpdateOffline()
{
	NetworkState state = NetworkManager::GetInstance()->GetNetworkState();

	// 切断中
	if (state == NW_STATE_DISCONNECT)
	{
		// Enterで接続
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			// 接続
			NetworkManager::GetInstance()->Connect();
		}
	}
}

void UpdateOnline()
{
	// Ctrl + Q で切断
	if ((CheckHitKey(KEY_INPUT_LCONTROL) || CheckHitKey(KEY_INPUT_RCONTROL)) && CheckHitKey(KEY_INPUT_Q))
	{
		// 切断
		NetworkManager::GetInstance()->Disconnect();
	}

}

void Draw()
{
	NetworkGameState state = NetworkManager::GetInstance()->GetNetworkGameState();
	switch (state)
	{
	case GAME_STATE_OFFLINE: DrawOffline(); break;
	case GAME_STATE_ONLINE: DrawOnline(); break;
	}
}

void DrawOffline()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Enterで接続");
}

void DrawOnline()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Ctrl + Qで切断");
	NetworkManager::GetInstance()->Draw();
}
