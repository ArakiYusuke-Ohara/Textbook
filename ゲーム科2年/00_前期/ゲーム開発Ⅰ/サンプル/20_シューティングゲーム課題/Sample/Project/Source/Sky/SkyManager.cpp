#include "SkyManager.h"
#include "Sky.h"
#include "../Level/LevelManager.h"

SkyManager* SkyManager::m_Instance = nullptr;

// こういうデータ群はエクセルにまとめたい
const char* SKY_MODEL_PATH[] =
{
	"Data/Sky/BlueSky.x",
};

SkyManager::SkyManager()
{
	m_Sky = nullptr;
}

SkyManager::~SkyManager()
{
	Fin();
}

void SkyManager::Init()
{
	// 空を生成する
	m_Sky = new Sky;
}

void SkyManager::Load()
{
	// 選択されたレベルのパラメータを取得
	const LevelParameter* levelParam = LevelManager::GetInstance()->GetSelectLevelParameter();

	// 空のIDから使うデータを引っ張ってきてロードする
	int skyID = levelParam->skyID;
	const char* path = SKY_MODEL_PATH[skyID];
	m_Sky->Load(path);
}

void SkyManager::Start()
{
	m_Sky->Start();
}

void SkyManager::Step()
{
	m_Sky->Step();
}

void SkyManager::Update()
{
	m_Sky->Update();
}

void SkyManager::Draw()
{
	m_Sky->Draw();
}

void SkyManager::Fin()
{
	delete m_Sky;
}

