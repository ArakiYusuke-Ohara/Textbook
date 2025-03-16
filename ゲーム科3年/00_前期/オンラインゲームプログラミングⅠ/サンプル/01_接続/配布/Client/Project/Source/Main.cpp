#include "DxLib.h"
#include "Network/Client.h"

// クライアント用グローバル変数
Client* g_Client = nullptr;

// 関数のプロトタイプ宣言
void Update();			// 更新
void Draw();			// 描画
void UpdateOffline();	// オフライン中の更新
void UpdateOnline();	// オンライン中の更新
void DrawOffline();		// オフライン中の描画
void DrawOnline();		// オンライン中の描画

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

	// クライアント生成
	g_Client = new Client();

	// IPアドレスを設定
	IPDATA ipData;
	ipData.d1 = 192;
	ipData.d2 = 168;
	ipData.d3 = 132;
	ipData.d4 = 107;
	g_Client->SetIPAddress(ipData);

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
	NetworkGameState state = g_Client->GetNetworkGameState();
	switch (state)
	{
	case GAME_STATE_OFFLINE: UpdateOffline(); break;
	case GAME_STATE_ONLINE: UpdateOnline(); break;
	}

	// ネットワークマネージャー更新
	g_Client->Update();

}

void UpdateOffline()
{
	NetworkState state = g_Client->GetNetworkState();

	// 切断中
	if (state == NW_STATE_DISCONNECT)
	{
		// Enterで接続
		if (CheckHitKey(KEY_INPUT_RETURN))
		{
			// 接続
			g_Client->Connect();
		}
	}
}

void UpdateOnline()
{
	// Ctrl + Q で切断
	if ((CheckHitKey(KEY_INPUT_LCONTROL) || CheckHitKey(KEY_INPUT_RCONTROL)) && CheckHitKey(KEY_INPUT_Q))
	{
		// 切断
		g_Client->Disconnect();
	}

}

void Draw()
{
	NetworkGameState state = g_Client->GetNetworkGameState();
	switch (state)
	{
	case GAME_STATE_OFFLINE: DrawOffline(); break;
	case GAME_STATE_ONLINE: DrawOnline(); break;
	}

	DrawString(0, 880, "クライアント側", GetColor(255, 255, 255));
}

void DrawOffline()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Enterで接続");
}

void DrawOnline()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Ctrl + Qで切断");
	g_Client->Draw();
}
