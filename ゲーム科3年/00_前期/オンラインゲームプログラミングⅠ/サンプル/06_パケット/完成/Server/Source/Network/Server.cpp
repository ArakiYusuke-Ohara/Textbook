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
	ReceiveData();
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
	NetworkPlayerData player;

	player.client.handle = handle;
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(handle, &player.client.ip);

	// ユーザー配列に追加
	m_NetworkPlayerData.push_back(player);

	// ログインデータを送信
	SendLoginData();
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
		// 削除するユーザーをハンドルから検索
		if ((*itr).client.handle == handle)
		{
			// 見つかったら削除して終了
			m_NetworkPlayerData.erase(itr);
			return;
		}
	}
}

void Server::ReceiveData()
{
	bool isUpdate = false;

	// 接続しているクライアント全員分処理する
	for (const NetworkPlayerData& player : m_NetworkPlayerData)
	{
		// クライアントから送られたデータのサイズを取得
		int dataLength = GetNetWorkDataLength(player.client.handle);

		// データが送られてきたかチェック
		if (dataLength > 0)
		{
		}
	}
}

void Server::SendLoginData()
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(LoginData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.packet = Packet::LOGIN;
	header.size = sizeof(LoginData);

	// 入ってきた順番をそのままIDにする
	LoginData data = {};
	data.playerID = (int)m_NetworkPlayerData.size();

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(LoginData));

	// 全クライアントに送信する
	for (const NetworkPlayerData& player : m_NetworkPlayerData)
	{
		NetWorkSend(player.client.handle, reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
	}
}
