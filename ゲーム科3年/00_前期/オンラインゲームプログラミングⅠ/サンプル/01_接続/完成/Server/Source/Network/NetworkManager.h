#pragma once
#include "DxLib.h"
#include <vector>

// サーバー側のNetworkManager

struct UserData
{
	int handle;
	IPDATA ip;
};

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new NetworkManager; }
	static NetworkManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Init();
	void Update();
	void Draw();
	void Fin();

private:
	void AddUserData(int handle);

private:
	static NetworkManager* m_Instance;
	std::vector<UserData> m_UserData;
};
