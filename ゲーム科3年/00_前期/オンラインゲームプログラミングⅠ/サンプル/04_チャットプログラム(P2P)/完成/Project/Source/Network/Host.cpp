#include "Host.h"
#include "../Input/InputString.h"

Host::Host()
{
	m_ClientIP = {};
}

Host::~Host()
{
}

void Host::StartNetwork()
{
	// マッチング開始
	int success = PreparationListenNetWork(PORT_NUMBER);

	// マッチング待ち状態へ
	m_NWState = NW_STATE_WAITING;
}

void Host::UpdateWaiting()
{
	// 新しい接続があったらそのネットワークハンドルを得る
	int acceptHandle = GetNewAcceptNetWork();
	// 新しい接続があった
	if (acceptHandle != -1)
	{
		// マッチングしたユーザーデータを設定
		m_PartnerHandle = acceptHandle;
		// 接続してきたマシンのＩＰアドレスを得る
		GetNetWorkIP(m_PartnerHandle, &m_ClientIP);

		// メッセージ入力開始
		m_MessageInput->Start();

		// 接続完了
		m_NWState = NW_STATE_INPUT_MESSAGE;
	}
}

void Host::DrawWaiting()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "マッチング中...");
}
