#include "DxLib.h"
#include "../Input/Input.h"
#include "Client.h"
#include "NetworkCommonParam.h"
#include "../Input/InputString.h"

Client::Client()
{
	m_HostHandle = 0;
	m_Mode = MODE_NONE;
	m_NWState = NW_STATE_NONE;
	m_MatchingClientData = {};
	m_IPAddress = {};
	m_SendChatData = {};
	m_UserNameInput = nullptr;
	m_MessageInput = nullptr;
	m_SendChatData = {};
	m_ChatData = {};
}

Client::~Client()
{
	Fin();
}

void Client::Init()
{
	// キー文字列入力システム設定
	m_UserNameInput = new InputString;
	m_MessageInput = new InputString;

	m_UserNameInput->SetPos(VGet(0.0f, 20.0f, 0.0f));
	m_MessageInput->SetPos(VGet(0.0f, 20.0f, 0.0f));

	// 最初はユーザー名入力
	m_NWState = NW_STATE_INPUT_USER_NAME;
}

void Client::Update()
{
	switch (m_NWState)
	{
		case NW_STATE_INPUT_USER_NAME:		UpdateDisconnect(); break;
		case NW_STATE_WAITING_CONNECTION:	UpdateWaitingConnection(); break;
		case NW_STATE_CONNECT:				UpdateConnect(); break;
	}
}

void Client::Draw()
{
	if (m_NWState == NW_STATE_INPUT_USER_NAME)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "ユーザー名を入力");
	}
	else if (m_NWState == NW_STATE_CONNECT)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "メッセージを入力");
		DrawFormatString(0, 840, GetColor(255, 255, 255), "Ctrl + Qで切断");
		DrawFormatString(0, 860, GetColor(255, 255, 255), "接続先IPアドレス：%d.%d.%d.%d", m_IPAddress.d1, m_IPAddress.d2, m_IPAddress.d3, m_IPAddress.d4);
	}

	DrawString(0, 880, "クライアント側", GetColor(255, 255, 255));

	m_UserNameInput->Draw();
	m_MessageInput->Draw();

	DrawChat();
}

void Client::Fin()
{
	// 状態が接続中以降であれば切断
	if (m_NWState >= NW_STATE_WAITING_CONNECTION)
	{
		Disconnect();
	}

	// 入力システム削除
	delete m_UserNameInput;
	delete m_MessageInput;
}

/// <summary>
/// サーバーに接続する
/// </summary>
void Client::Connect()
{
	// 指定したIPアドレスの端末に接続
	m_HostHandle = ConnectNetWork(m_IPAddress, PORT_NUMBER);

	// ハンドルが-1なら接続できてない
	if (m_HostHandle == -1)
	{
		// 名前入力に戻る
		m_UserNameInput->Start();
	}
	else
	{
		// 接続待ちへ
		m_NWState = NW_STATE_WAITING_CONNECTION;
	}
}

/// <summary>
/// サーバーから切断する
/// </summary>
void Client::Disconnect()
{
	// 切断
	CloseNetWork(m_HostHandle);
	m_HostHandle = 0;
	m_NWState = NW_STATE_INPUT_USER_NAME;

	// メッセージ入力終了
	m_MessageInput->Fin();
	// ユーザー名入力開始
	m_UserNameInput->Start();
}

/// <summary>
/// 切断中の更新処理
/// </summary>
void Client::UpdateDisconnect()
{
	// ユーザー名入力更新
	m_UserNameInput->Update();

	// Enterで接続
	if (Input::IsTriggerKey(KEY_ENTER))
	{
		// 入力した名前を取得
		const char* name = m_UserNameInput->GetInputString();

		// 文字数チェック
		int nameLen = (int)strlen(name);
		if (nameLen > 0)
		{
			// ユーザー名をチャットデータに記録
			strcpy_s(m_SendChatData.name, NETWORK_USER_NAME_BUFFER_MAX, name);

			// ユーザー名入力終了
			m_UserNameInput->Fin();

			// 通信開始
			StartNetwork();
			m_NWState = NW_STATE_WAITING;

			// クライアントならホストに接続
			if (m_Mode == MODE_CLIENT)
			{
				Connect();
				m_NWState = NW_STATE_WAITING_CONNECTION;
			}
		}
	}
}

/// <summary>
/// 接続待ち
/// </summary>
void Client::UpdateWaiting()
{
	if (WaitingConnection())
	{
		// メッセージ入力開始
		m_MessageInput->Start();

		// 接続完了
		m_NWState = NW_STATE_CONNECT;
	}
}

/// <summary>
/// クライアント専用接続待機中の更新処理
/// </summary>
void Client::UpdateWaitingConnection()
{
	if (m_Mode != MODE_CLIENT) return;

	// 接続できたかチェック
	if (GetNetWorkAcceptState(m_HostHandle))
	{
		// 接続完了
		m_NWState = NW_STATE_CONNECT;

		// メッセージ入力開始
		m_MessageInput->Start();
	}
}

/// <summary>
/// 接続中の更新処理
/// </summary>
void Client::UpdateConnect()
{
	// メッセージ入力更新
	m_MessageInput->Update();

	// Enterキーでユーザー名とメッセージをサーバーに送信
	if (Input::IsTriggerKey(KEY_ENTER))
	{
		// 入力メッセージを取得
		const char* message = m_MessageInput->GetInputString();

		// 文字数チェック
		int messageLen = (int)strlen(message);
		if (messageLen > 0)
		{
			// メッセージをチャットデータに設定
			strcpy_s(m_SendChatData.message, NETWORK_MESSAGE_BUFFER_MAX, message);
			// 自分のメッセージは自分で追加
			m_ChatData.push_back(m_SendChatData);

			// 相手側に送信
			int nwHandle = m_Mode == MODE_HOST ? m_MatchingClientData.handle : m_HostHandle;
			NetWorkSend(nwHandle, &m_SendChatData, sizeof(m_SendChatData));

			// メッセージをクリア
			m_MessageInput->Clear();
		}
	}

	// Ctrl + Q で切断
	if ((Input::IsInputKey(KEY_CTRL_L) || Input::IsInputKey(KEY_CTRL_R)) && Input::IsTriggerKey(KEY_Q))
	{
		// 切断
		Disconnect();
	}

	// データ受信
	ReceiveData();
}

void Client::ReceiveData()
{
	int nwHandle = m_Mode == MODE_HOST ? m_MatchingClientData.handle : m_HostHandle;
	// クライアントから送られたデータのサイズを取得
	int dataLength = GetNetWorkDataLength(nwHandle);

	// データが送られてきたかチェック
	if (dataLength > 0)
	{
		// 受信
		ChatData receivedData = {};
		NetWorkRecv(nwHandle, &receivedData, sizeof(receivedData));

		// 受信したデータをチャットに追加
		m_ChatData.push_back(receivedData);
	}
}

/// <summary>
/// チャット内容を描画
/// </summary>
void Client::DrawChat()
{
	int raw = 0;
	for (ChatData data : m_ChatData)
	{
		DrawFormatString(0, 40 + raw * 20, GetColor(255, 255, 255), "%s: %s", data.name, data.message);
		raw++;
	}
}

