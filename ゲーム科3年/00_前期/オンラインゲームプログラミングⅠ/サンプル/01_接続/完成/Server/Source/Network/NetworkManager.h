#pragma once
#include <vector>

// サーバー側のNetworkManager

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
	static NetworkManager* m_Instance;
	std::vector<int> m_UserHandles;
};
