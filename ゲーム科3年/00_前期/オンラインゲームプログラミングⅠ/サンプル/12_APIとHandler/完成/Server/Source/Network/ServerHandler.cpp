#include "ServerHandler.h"
#include "NetworkUtility.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"

using namespace Network;

/// <summary>
/// ログイン
/// </summary>
void ServerHandler::HandleLogin(int nwHandle)
{
	// ログインデータを受信
	Network::RequestLoginData request = {};
	NetWorkRecv(nwHandle, &request, sizeof(request));

	// ID設定
	ResponseLoginData response = {};
	memset(&response, -1, sizeof(response));
	int i = 0;
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (const auto& player : players)
	{
		response.playerID[i] = player->GetID();
		response.selfID = player->GetID();	// 末尾にあるIDがログインしたクライアント自身のIDとなる（よくない）
		i++;
	}

	// ログインするクライアントに送信する
	auto buffer = MakePacket<ResponseLoginData>(PacketType::LOGIN, response);
	NetWorkSend(nwHandle, reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
}

/// <summary>
/// ジョイン
/// </summary>
void ServerHandler::HandleJoin()
{
}

/// <summary>
/// ログアウト
/// </summary>
void ServerHandler::HandleLogout()
{
}
