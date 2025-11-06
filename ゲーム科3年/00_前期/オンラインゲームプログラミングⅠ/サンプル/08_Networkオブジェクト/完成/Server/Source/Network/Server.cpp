#include "DxLib.h"
#include "Server.h"
#include "NetworkCommonParam.h"
#include <vector>

using namespace Network;

Server::Server()
{
	m_NetworkPlayerData = {};
}

Server::~Server()
{
	Fin();
}

void Server::Init()
{
	// 接続してくるのを待つ状態にする
	int success = PreparationListenNetWork(PORT_NUMBER);
}

void Server::Update()
{
	// 新しい接続があったらそのネットワークハンドルを得る
	int acceptHandle = GetNewAcceptNetWork();
	// 新しい接続があった
	if (acceptHandle != -1)
	{
		AddUserData(acceptHandle);
	}

	// 切断があったらそのネットワークハンドルを得る
	int lostHandle = GetLostNetWork();
	// 切断があった
	if (lostHandle != -1)
	{
		RemoveUserData(lostHandle);
	}

	// データ受信処理


	// データ更新があればクライアントに送信して同期

}

void Server::Draw()
{
}

void Server::Fin()
{
	m_NetworkPlayerData.clear();
}

/// <summary>
/// ユーザーデータを追加する
/// </summary>
/// <param name="handle">追加するユーザーのハンドル</param>
void Server::AddUserData(int handle)
{
	NetworkPlayerData player = {};

	player.id = (int)m_NetworkPlayerData.size();
	player.client.handle = handle;
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(handle, &player.client.ip);

	// 初期設定
	player.pos = { 100.0f, 100.0f, 0.0f };
	player.scale = { 1.0f, 1.0f, 1.0f };

	// ユーザー配列に追加
	m_NetworkPlayerData.push_back(player);

	// ログインデータを送信
	SendLoginData(player);

	// 参加データを送信
	SendJoinData(player);

	// 全員の座標を同期

}

/// <summary>
/// ユーザーデータを取り除く
/// </summary>
/// <param name="handle">取り除くユーザーのハンドル</param>
void Server::RemoveUserData(int handle)
{
	// イテレータを使って部分削除する
	for(auto itr = m_NetworkPlayerData.begin(); itr != m_NetworkPlayerData.end(); itr++)
	{
		const NetworkPlayerData& player = (*itr);
		// 削除するユーザーをハンドルから検索
		if (player.client.handle == handle)
		{
			// ログアウトをクライアントに送信
			SendLogoutData(player.id);

			// 見つかったら削除して終了
			m_NetworkPlayerData.erase(itr);
			return;
		}
	}
}

void Server::SendLoginData(const NetworkPlayerData& loginPlayer)
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(LoginData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.type = PacketType::LOGIN;
	header.size = sizeof(LoginData);

	// ID設定
	LoginData data = {};
	memset(&data, -1, sizeof(data));
	int i = 0;
	for (const auto& player : m_NetworkPlayerData)
	{
		data.playerID[i] = player.id;				
		data.selfID = player.id;	// 末尾にあるIDがログインしたクライアント自身のIDとなる
		i++;
	}

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(LoginData));

	// ログインするクライアントに送信する
	NetWorkSend(loginPlayer.client.handle, reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
}

void Server::SendJoinData(const NetworkPlayerData& joinPlayer)
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(JoinData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.type = PacketType::JOIN;
	header.size = sizeof(JoinData);

	// ID設定
	JoinData data = {};
	data.playerID = joinPlayer.id;

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(JoinData));

	// 参加するクライアント以外の全クライアントに送信する
	for (const NetworkPlayerData& player : m_NetworkPlayerData)
	{
		if (player.id != joinPlayer.id)
		{
			NetWorkSend(player.client.handle, reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
		}
	}

}

void Server::SendLogoutData(int id)
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(LogoutData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.type = PacketType::LOGOUT;
	header.size = sizeof(LogoutData);

	// ID設定
	LogoutData data = {};
	data.playerID = id;

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(LogoutData));

	// 全クライアントに送信する
	for (const NetworkPlayerData& player : m_NetworkPlayerData)
	{
		NetWorkSend(player.client.handle, reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
	}
}
