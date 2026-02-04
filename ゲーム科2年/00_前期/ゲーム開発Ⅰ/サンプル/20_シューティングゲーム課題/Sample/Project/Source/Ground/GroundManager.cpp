#include "GroundManager.h"
#include "Ground.h"
#include "../Level/LevelManager.h"

GroundManager* GroundManager::m_Instance = nullptr;

// こういうデータ群はエクセルにまとめたい
struct GroundParameter
{
	char path[64];
	float baseScrollSpeed;
};
GroundParameter GROUND_MASTER_PARAM[] =
{
	{
		"Data/Ground/Grass.x",
		0.001f
	},
	{
		"Data/Ground/Cyber.x",
		0.001f
	}
};

GroundManager::GroundManager()
{
	m_Ground = nullptr;
}

GroundManager::~GroundManager()
{
	Fin();
}

void GroundManager::Init()
{
	// 空を生成する
	m_Ground = new Ground;
}

void GroundManager::Load()
{
	// 選択されたレベルのパラメータを取得
	const LevelParameter* levelParam = LevelManager::GetInstance()->GetSelectLevelParameter();

	// 空のIDからパラメータを引っ張ってくる
	int groundID = levelParam->groundID;
	GroundParameter param = GROUND_MASTER_PARAM[groundID];

	// パラメータから各種設定
	m_Ground->Load(param.path);
	m_Ground->SetScrollSpeed(param.baseScrollSpeed);
}

void GroundManager::Start()
{
	m_Ground->Start();
}

void GroundManager::Step()
{
	m_Ground->Step();
}

void GroundManager::Update()
{
	m_Ground->Update();
}

void GroundManager::Draw()
{
	m_Ground->Draw();
}

void GroundManager::Fin()
{
	delete m_Ground;
}

