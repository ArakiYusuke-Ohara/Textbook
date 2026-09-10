#pragma once
#include "../Resource/ResourceParameter.h"

enum BlockID
{
	BLOCK_ID_GRASS,
	BLOCK_ID_MAX
};

struct BlockData
{
	BlockID blockID;
	ModelID modelID;
};

const BlockData BLOCK_MASTER_DATA[] =
{
	{BLOCK_ID_GRASS, MODEL_ID_GRASS},
};
