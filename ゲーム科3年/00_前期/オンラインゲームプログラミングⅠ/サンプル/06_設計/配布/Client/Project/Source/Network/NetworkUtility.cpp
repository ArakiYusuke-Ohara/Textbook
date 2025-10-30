#include "NetworkUtility.h"

namespace Network
{
	std::vector<uint8_t> NetworkUtility::MakePosData(const PosData& data)
	{
		// 通信データサイズ
		size_t dataSize = sizeof(PacketHeader) + sizeof(PosData);

		// パケット ＋ データを格納するバッファー
		std::vector<uint8_t> buffer(dataSize);

		// パケット作成
		PacketHeader header = {};
		header.packet = Packet::POS;
		header.size = sizeof(PosData);

		// パケットをバッファーに入れる
		memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
		// パケットの後ろにデータを入れる
		memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(PosData));

		return buffer;
	}

	std::vector<uint8_t> NetworkUtility::MakeRotData(const RotData& data)
	{
		// 通信データサイズ
		size_t dataSize = sizeof(PacketHeader) + sizeof(RotData);

		// パケット ＋ データを格納するバッファー
		std::vector<uint8_t> buffer(dataSize);

		// パケット作成
		PacketHeader header = {};
		header.packet = Packet::ROT;
		header.size = sizeof(RotData);

		// パケットをバッファーに入れる
		memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
		// パケットの後ろにデータを入れる
		memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(RotData));

		return buffer;
	}

	std::vector<uint8_t> NetworkUtility::MakeScaleData(const ScaleData& data)
	{
		// 通信データサイズ
		size_t dataSize = sizeof(PacketHeader) + sizeof(ScaleData);

		// パケット ＋ データを格納するバッファー
		std::vector<uint8_t> buffer(dataSize);

		// パケット作成
		PacketHeader header = {};
		header.packet = Packet::SCALE;
		header.size = sizeof(ScaleData);

		// パケットをバッファーに入れる
		memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
		// パケットの後ろにデータを入れる
		memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(ScaleData));

		return buffer;
	}

}
