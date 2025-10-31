#pragma once

// NetworkCommonParam.hはクライアント/サーバー共通のパラメータ
// 必ず双方で同じ状態にする必要がある

// ポート番号は49152～65535が好ましい
#define PORT_NUMBER 50000

namespace Network
{
	// パケットの種類（符号なし8ビットで扱う）
	enum class PacketType : uint8_t
	{
		LOGIN,
		JOIN,
		LOGOUT,
	};

	// 全通信に使用するパケットデータ
	struct PacketHeader
	{
		PacketType type;	// 種類
		uint16_t size;	// データサイズ（符号なし16ビット）
	};
}


