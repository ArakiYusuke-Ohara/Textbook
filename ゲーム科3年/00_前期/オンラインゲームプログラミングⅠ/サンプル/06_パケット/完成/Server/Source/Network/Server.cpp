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
	bool isUpdate = ReceiveData();

	// データ更新があればクライアントに送信して同期
	if (isUpdate)
	{
		SendAllTransformData();
	}
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

	// スケールは1にしておく
	player.scale = { 1.0f, 1.0f, 1.0f };

	// ユーザー配列に追加
	m_NetworkPlayerData.push_back(player);

	// ログインデータを送信
	SendLoginData(player);

	// 参加データを送信
	SendJoinData(player);

	// 全員の座標を同期
	SendAllTransformData();
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

bool Server::ReceiveData()
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
			// ヘッダーのみを受信
			PacketHeader header = {};
			NetWorkRecv(player.client.handle, reinterpret_cast<char*>(&header), sizeof(header));

			// パケットごとの処理
			switch (header.packet)
			{
				case Packet::POS:	SyncPos(player.client.handle); break;	// 座標を同期
				case Packet::ROT:	SyncRot(player.client.handle); break;	// 回転を同期
				case Packet::SCALE: SyncScale(player.client.handle); break;	// 拡縮を同期
			}

			// 更新された
			isUpdate = true;
		}
	}

	return isUpdate;
}

void Server::SendLoginData(const NetworkPlayerData& loginPlayer)
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(LoginData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.packet = Packet::LOGIN;
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
	header.packet = Packet::JOIN;
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
	header.packet = Packet::LOGOUT;
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

void Server::SendAllTransformData()
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(AllTransformData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.packet = Packet::ALL_TRANSFORM;
	header.size = sizeof(AllTransformData);

	// データ設定
	AllTransformData data = {};
	int i = 0;
	for (const auto& playerData : m_NetworkPlayerData)
	{
		data.pos[i] = playerData.pos;
		data.rot[i] = playerData.rot;
		data.scale[i] = playerData.scale;
		i++;
	}

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(AllTransformData));

	// 全クライアントに送信する
	for (const NetworkPlayerData& player : m_NetworkPlayerData)
	{
		NetWorkSend(player.client.handle, reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
	}
}

/// <summary>
/// クライアントから座標が送られたら情報を更新
/// 最新の座標を全クライアントに送り同期する
/// </summary>
void Server::SyncPos(int handle)
{
	// 座標データを受信
	Network::PosData data = {};
	NetWorkRecv(handle, &data, sizeof(data));

	for (NetworkPlayerData& player : m_NetworkPlayerData)
	{
		// IDが一致したプレイヤーの座標を更新する
		if (player.id == data.playerID)
		{
			player.pos = data.pos;
			break;
		}
	}
}

void Server::SyncRot(int handle)
{
	// 座標データを受信
	Network::RotData data = {};
	NetWorkRecv(handle, &data, sizeof(data));

	for (NetworkPlayerData& player : m_NetworkPlayerData)
	{
		// IDが一致したプレイヤーの座標を更新する
		if (player.id == data.playerID)
		{
			player.rot = data.rot;
			break;
		}
	}
}

void Server::SyncScale(int handle)
{
	// 座標データを受信
	Network::ScaleData data = {};
	NetWorkRecv(handle, &data, sizeof(data));

	for (NetworkPlayerData& player : m_NetworkPlayerData)
	{
		// IDが一致したプレイヤーの座標を更新する
		if (player.id == data.playerID)
		{
			player.scale = data.scale;
			break;
		}
	}
}
