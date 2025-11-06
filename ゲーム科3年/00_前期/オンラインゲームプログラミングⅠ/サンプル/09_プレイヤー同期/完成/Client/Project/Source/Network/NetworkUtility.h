#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include <vector>

namespace Network
{
	inline std::vector<uint8_t> MakePosData(const PosData& data)
	{
		// 通信データサイズ
		size_t dataSize = sizeof(PacketHeader) + sizeof(PosData);

		// パケット ＋ データを格納するバッファー
		std::vector<uint8_t> buffer(dataSize);

		// パケット作成
		PacketHeader header = {};
		header.type = PacketType::POS;
		header.size = sizeof(PosData);

		// パケットをバッファーに入れる
		memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
		// パケットの後ろにデータを入れる
		memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(PosData));

		return buffer;
	}

	inline std::vector<uint8_t> MakeRotData(const RotData& data)
	{
		// 通信データサイズ
		size_t dataSize = sizeof(PacketHeader) + sizeof(RotData);

		// パケット ＋ データを格納するバッファー
		std::vector<uint8_t> buffer(dataSize);

		// パケット作成
		PacketHeader header = {};
		header.type = PacketType::ROT;
		header.size = sizeof(RotData);

		// パケットをバッファーに入れる
		memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
		// パケットの後ろにデータを入れる
		memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(RotData));

		return buffer;
	}

	inline std::vector<uint8_t> MakeScaleData(const ScaleData& data)
	{
		// 通信データサイズ
		size_t dataSize = sizeof(PacketHeader) + sizeof(ScaleData);

		// パケット ＋ データを格納するバッファー
		std::vector<uint8_t> buffer(dataSize);

		// パケット作成
		PacketHeader header = {};
		header.type = PacketType::SCALE;
		header.size = sizeof(ScaleData);

		// パケットをバッファーに入れる
		memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
		// パケットの後ろにデータを入れる
		memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(ScaleData));

		return buffer;
	}

	inline std::vector<uint8_t> MakeTransformData(const TransformData& data)
	{
		// 通信データサイズ
		size_t dataSize = sizeof(PacketHeader) + sizeof(TransformData);

		// パケット ＋ データを格納するバッファー
		std::vector<uint8_t> buffer(dataSize);

		// パケット作成
		PacketHeader header = {};
		header.type = PacketType::TRANSFORM;
		header.size = sizeof(TransformData);

		// パケットをバッファーに入れる
		memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
		// パケットの後ろにデータを入れる
		memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(TransformData));

		return buffer;
	}
}

