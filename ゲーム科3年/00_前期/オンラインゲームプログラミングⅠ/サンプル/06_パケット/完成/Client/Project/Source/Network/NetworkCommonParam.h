#pragma once
#include <cstdint>

// NetworkCommonParam.hはクライアント/サーバー共通のパラメータ
// 必ず双方で同じ状態にする必要がある

// ポート番号は49152～65535が好ましい
#define PORT_NUMBER 50000

// プレイヤー最大人数
#define NETWORK_PLAYER_MAX 4

namespace Network
{

	// 通信できるユーザー名のMAXサイズ（全角5文字まで）
	constexpr int NETWORK_USER_NAME_MAX = 10;
	// 文字列の長さは文字数＋終端文字
	constexpr int NETWORK_USER_NAME_BUFFER_MAX = NETWORK_USER_NAME_MAX + 1;

	// 通信できる文字列のMAXサイズ（全角20文字まで）
	constexpr int NETWORK_MESSAGE_MAX = 40;
	// 文字列の長さは文字数＋終端文字
	constexpr int NETWORK_MESSAGE_BUFFER_MAX = NETWORK_MESSAGE_MAX + 1;

	// パケットの種類（符号なし8ビットで扱う）
	enum class Packet : uint8_t
	{
		LOGIN,
		JOIN,
		LOGOUT,
		POS,
	};

	// 全通信に使用するパケットデータ
	struct PacketHeader
	{
		Packet packet;	// 種類
		uint16_t size;	// データサイズ（符号なし16ビット）
	};

	// プレイヤーログインデータ
	struct LoginData
	{
		int selfID;
		int playerID[NETWORK_PLAYER_MAX];
	};

	// 他プレイヤー参加データ
	struct JoinData
	{
		int playerID;
	};

	// プレイヤーログアウトデータ
	struct LogoutData
	{
		int playerID;
	};

	// プレイヤーの座標データ
	struct PosData
	{
		int playerID;
		float x;
		float y;
		float z;
	};
}

