#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include <vector>

namespace Network
{
	class NetworkUtility
	{
	public:
		static std::vector<uint8_t> MakePosData(const PosData& data);
		static std::vector<uint8_t> MakeRotData(const RotData& data);
		static std::vector<uint8_t> MakeScaleData(const ScaleData& data);
	};
}

