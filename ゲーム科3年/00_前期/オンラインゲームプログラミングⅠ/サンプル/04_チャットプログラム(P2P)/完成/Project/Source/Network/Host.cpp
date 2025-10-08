#include "Host.h"

Host::Host()
{
}

Host::~Host()
{
}

void Host::SetUserData(int handle)
{
	m_MatchingClientData.handle = handle;
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(handle, &m_MatchingClientData.ip);
}

void Host::StartNetwork()
{
	int success = PreparationListenNetWork(PORT_NUMBER);
}

bool Host::WaitingConnection()
{
	// 新しい接続があったらそのネットワークハンドルを得る
	int acceptHandle = GetNewAcceptNetWork();
	// 新しい接続があった
	if (acceptHandle != -1)
	{
		// マッチングしたユーザーデータを設定
		SetUserData(acceptHandle);

		return true;
	}

	return false;
}
