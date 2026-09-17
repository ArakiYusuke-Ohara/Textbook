#pragma once
#include "../Resource/ResourceParameter.h"

enum BlockID
{
	BLOCK_ID_GRASS,
	BLOCK_ID_MAX
};

struct BlockParameter
{
	BlockID blockID;
	ModelID modelID;
};

extern const BlockParameter BLOCK_MASTER_PARAM[];