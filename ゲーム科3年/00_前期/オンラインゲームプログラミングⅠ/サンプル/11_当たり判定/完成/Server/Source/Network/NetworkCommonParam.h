#pragma once
#include "DxLib.h"
#include <cstdint>

// NetworkCommonParam.hはクライアント/サーバー共通のパラメータ
// 必ず双方で同じ状態にする必要がある

namespace Network
{
	// ポート番号
	constexpr int PORT_NUMBER = 50000;
	// プレイヤー最大人数
	constexpr int PLAYER_MAX = 4;
	// プレイヤーサイズ
	constexpr int PLAYER_WIDTH = 64;
	constexpr int PLAYER_HEIGHT = 64;

	// パケットの種類（符号なし8ビットで扱う）
	enum class PacketType : uint8_t
	{
		LOGIN,
		JOIN,
		LOGOUT,
		POS,
		ROT,
		SCALE,
		TRANSFORM,
		ALL_TRANSFORM
	};

	// 全通信に使用するパケットデータ
	struct PacketHeader
	{
		PacketType type;	// 種類
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
		VECTOR pos;
	};

	// プレイヤーの回転データ
	struct RotData
	{
		int playerID;
		VECTOR rot;
	};

	// プレイヤーの拡縮データ
	struct ScaleData
	{
		int playerID;
		VECTOR scale;
	};

	struct TransformData
	{
		int playerID;
		VECTOR pos;
		VECTOR rot;
		VECTOR scale;
	};

	// 全プレイヤーのトランスフォームデータ
	struct AllTransformData
	{
		VECTOR pos[NETWORK_PLAYER_MAX];
		VECTOR rot[NETWORK_PLAYER_MAX];
		VECTOR scale[NETWORK_PLAYER_MAX];
	};
}

