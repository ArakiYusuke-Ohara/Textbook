#include "DxLib.h"
#include "NetworkManager.h"
#include "NetworkCommonParam.h"

NetworkManager* NetworkManager::m_Instance = nullptr;

NetworkManager::NetworkManager()
{
	m_UserHandles = {};
}

NetworkManager::~NetworkManager()
{
	Fin();
}

void NetworkManager::Init()
{
	// 接続してくるのを待つ状態にする
	PreparationListenNetWork(PORT_NUMBER);
}

void NetworkManager::Update()
{
	// 新しい接続があったらそのネットワークハンドルを得る


}

void NetworkManager::Draw()
{

}

void NetworkManager::Fin()
{
}
