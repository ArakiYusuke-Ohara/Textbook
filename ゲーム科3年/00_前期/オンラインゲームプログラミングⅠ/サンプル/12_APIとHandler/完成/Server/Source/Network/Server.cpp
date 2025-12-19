#include "DxLib.h"
#include "Server.h"
#include "ServerHandler.h"
#include "NetworkCommonParam.h"
#include "../Component/Collision/CollisionManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include <vector>

using namespace Network;

Server::Server()
{

}

Server::~Server()
{
	Fin();
}

void Server::Init()
{
	// サーバー用プレイヤー管理
	PlayerManager::CreateInstance();

	// 当たり判定はサーバー側でする
	CollisionManager::GetInstance()->CreateInstance();

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
		PlayerManager::GetInstance()->RemovePlayer(lostHandle);
	}

	// データ受信処理
	ReceiveData();
}

void Server::Draw()
{
#ifdef _DEBUG
	PlayerManager::GetInstance()->Draw();
	CollisionManager::GetInstance()->Draw();
#endif
}

void Server::Fin()
{
	// プレイヤー終了
	PlayerManager::DeleteInstance();

	// 当たり判定終了
	CollisionManager::DeleteInstance();
}

/// <summary>
/// ユーザーデータを追加する
/// </summary>
/// <param name="handle">追加するユーザーのハンドル</param>
void Server::AddUserData(int handle)
{
	// プレイヤー生成
	Player& player = PlayerManager::GetInstance()->CreatePlayer();
	player.Init(handle);

	// 参加データを送信
	SendJoinData(player);

	// 全員の座標を同期
	//SendAllTransformData();
}

void Server::ReceiveData()
{
	// 接続しているクライアント全員分処理する
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (const auto& player : players)
	{
		int nwHandle = player->GetNetworkHandle();
		// クライアントから送られたデータのサイズを取得
		int dataLength = GetNetWorkDataLength(nwHandle);

		// データが送られてきたかチェック
		if (dataLength > 0)
		{
			// ヘッダーのみを受信
			PacketHeader header = {};
			NetWorkRecv(nwHandle, reinterpret_cast<char*>(&header), sizeof(header));

			// パケットごとの処理
			switch (header.type)
			{
			case PacketType::LOGIN: ServerHandler::HandleLogin(nwHandle); break;					// ログイン
				case PacketType::TRANSFORM: SyncTransform(nwHandle); break;	// トランスフォームを同期
			}
		}
	}
}

void Server::SendLoginData(const Player& loginPlayer)
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(ResponseLoginData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.type = PacketType::LOGIN;
	header.size = sizeof(ResponseLoginData);

	// ID設定
	ResponseLoginData data = {};
	memset(&data, -1, sizeof(data));
	int i = 0;
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (const auto& player : players)
	{
		data.playerID[i] = player->GetID();				
		data.selfID = player->GetID();	// 末尾にあるIDがログインしたクライアント自身のIDとなる（よくない）
		i++;
	}

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(ResponseLoginData));

	// ログインするクライアントに送信する
	NetWorkSend(loginPlayer.GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
}

void Server::SendJoinData(const Player& joinPlayer)
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
	data.playerID = joinPlayer.GetID();

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(JoinData));

	// 参加するクライアント以外の全クライアントに送信する
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (const auto& player : players)
	{
		if (player->GetID() != joinPlayer.GetID())
		{
			NetWorkSend(player->GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
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
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (const auto& player : players)
	{
		NetWorkSend(player->GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
	}
}

void Server::SendAllTransformData()
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(AllTransformData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.type = PacketType::ALL_TRANSFORM;
	header.size = sizeof(AllTransformData);

	// データ設定
	AllTransformData data = {};
	int i = 0;
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (const auto& player : players)
	{
		data.pos[i] = player->GetPosition();
		data.rot[i] = player->GetRotation();
		data.scale[i] = player->GetScale();;
		i++;
	}

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(AllTransformData));

	// 全クライアントに送信する
	for (const auto& player : players)
	{
		NetWorkSend(player->GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
	}
}

/// <summary>
/// 座標の同期
/// </summary>
/// <param name="handle">受信したクライアントのハンドル</param>
void Server::SyncPos(int handle)
{
	// 座標データを受信
	Network::PosData data = {};
	NetWorkRecv(handle, &data, sizeof(data));

	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (auto& player : players)
	{
		// IDが一致したプレイヤーの座標を更新する
		if (player->GetID() == data.playerID)
		{
			player->SetPosition(data.pos);
			break;
		}
	}
}

/// <summary>
/// 回転の同期
/// </summary>
/// <param name="handle">受信したクライアントのハンドル</param>
void Server::SyncRot(int handle)
{
	// 回転データを受信
	Network::RotData data = {};
	NetWorkRecv(handle, &data, sizeof(data));

	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (auto& player : players)
	{
		// IDが一致したプレイヤーの回転を更新する
		if (player->GetID() == data.playerID)
		{
			player->SetRotation(data.rot);
			break;
		}
	}
}

/// <summary>
/// 拡縮の同期
/// </summary>
/// <param name="handle">受信したクライアントのハンドル</param>
void Server::SyncScale(int handle)
{
	// 拡縮データを受信
	Network::ScaleData data = {};
	NetWorkRecv(handle, &data, sizeof(data));

	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (auto& player : players)
	{
		// IDが一致したプレイヤーの拡縮を更新する
		if (player->GetID() == data.playerID)
		{
			player->SetScale(data.scale);
			break;
		}
	}
}

/// <summary>
/// トランスフォームの同期
/// </summary>
/// <param name="handle">受信したクライアントのハンドル</param>
void Server::SyncTransform(int handle)
{
	// トランスフォームデータを受信
	Network::TransformData data = {};
	NetWorkRecv(handle, &data, sizeof(data));

	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (auto& player : players)
	{
		// IDが一致したプレイヤーのトランスフォームを更新する
		if (player->GetID() == data.playerID)
		{
			player->SetPosition(data.pos);
			player->SetRotation(data.rot);
			player->SetScale(data.scale);
			break;
		}
	}

	// 当たり判定
	CheckCollision();

	// 全員の座標を同期
	SendAllTransformData();
}

void Server::CheckCollision()
{
	CollisionManager::GetInstance()->CheckCollision();
}
