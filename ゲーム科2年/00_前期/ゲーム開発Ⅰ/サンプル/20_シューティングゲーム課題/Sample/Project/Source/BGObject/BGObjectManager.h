#pragma once

#include "../Singleton/Singleton.h"
#include <vector>

class BGObject;

enum BGObjectType
{
	BGOBJECT_CUBE,
	BGOBJECT_TYPE_MAX,
};

class BGObjectManager : public Singleton<BGObjectManager>
{
public:
	BGObjectManager();
	~BGObjectManager();

public:
	void Load();
	void Update();
	void Draw();
	void Fin();

public:
	BGObject* Create(BGObjectType type);
	BGObject* Create(BGObjectType type, VECTOR pos, VECTOR rot = {}, VECTOR scale = {1.0f, 1.0f, 1.0f});

	void LocateRandom(float startZ = 0.0f);
	void UpdateRandomCreater();

private:
	BGObject* CreateRandom();
	void SetupFloatingMover(BGObject* object);

private:
	int m_Handles[BGOBJECT_TYPE_MAX];
	int m_Timer;
	std::vector<BGObject*> m_Objects;
};