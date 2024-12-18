#include "DxLib.h"
#include "BGObjectManager.h"
#include "BGObject.h"
#include "../MyRandom/MyRandom.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../ObjectMover/ObjectMoverManager.h"
#include "../ObjectMover/Floating.h"

BGObjectManager::BGObjectManager()
{
	// 配列全体を0で埋める
	std::fill(std::begin(m_Handles), std::end(m_Handles), 0);
	m_Timer = 0;
}

BGObjectManager::~BGObjectManager()
{
	Fin();
}

void BGObjectManager::Load()
{
	m_Handles[BGOBJECT_CUBE] = MV1LoadModel("Data/BGObject/Cube/Cube.x");
}

void BGObjectManager::Update()
{
	for (BGObject* object : m_Objects)
	{
		if (object->IsActive())
		{
			object->Update();
		}
	}
}

void BGObjectManager::Draw()
{
	for (BGObject* object : m_Objects)
	{
		if (object->IsActive())
		{
			object->Draw();
		}
	}
}

void BGObjectManager::Fin()
{
	for (int handle : m_Handles)
	{
		MV1DeleteModel(handle);
	}

	for (BGObject* object : m_Objects)
	{
		delete object;
	}

	m_Objects.clear();
}

BGObject* BGObjectManager::Create(BGObjectType type)
{
	// 未使用のオブジェクトを探す
	for (BGObject* object : m_Objects)
	{
		if (!object->IsActive() && type == object->GetType())
		{
			// 未使用のオブジェクトを使いまわす
			object->SetActive(true);
		}
	}

	// 未使用が無ければ新規追加する
	BGObject* object = new BGObject;
	object->Create(m_Handles[type]);
	object->SetType(type);
	m_Objects.push_back(object);

	return object;
}

BGObject* BGObjectManager::Create(BGObjectType type, VECTOR pos, VECTOR rot, VECTOR scale)
{
	BGObject* object = Create(type);
	object->SetPos(pos);
	object->SetRot(rot);
	object->SetScale(scale);

	return object;
}

void BGObjectManager::LocateRandom(float startZ)
{
	float posZ = startZ;
	while (posZ <= 1000.0f)
	{
		BGObject* object = CreateRandom();
		SetupFloatingMover(object);
		VECTOR pos = object->GetPos();
		pos.z = posZ;
		object->SetPos(pos);

		posZ += 20.0f;
	}
}

void BGObjectManager::UpdateRandomCreater()
{
	if (m_Timer <= 0)
	{
		BGObject* object = CreateRandom();
		SetupFloatingMover(object);
		m_Timer = 300;
	}
	else
	{
		m_Timer--;
	}
}

BGObject* BGObjectManager::CreateRandom()
{
	VECTOR pos = {};
	// X座標はランダムで10.0～20.0
	pos.x = MyRandom::GetDistributionF(20.0f, 30.0f);
	// 50%でマイナスにする
	if (MyRandom::GetBernoulli(0.5f))
	{
		pos.x = -pos.x;
	}

	// Y座標はランダムで10.0～40.0
	pos.y = MyRandom::GetDistributionF(10.0f, 40.0f);

	// とりあえずプレイヤーの先に出してみる
	float playerPosZ = PlayerManager::GetInstance()->GetPlayer()->GetPos().z;
	pos.z = playerPosZ + 200.0f;

	// 回転もランダム
	VECTOR rot = {};
	rot.x = MyRandom::GetDistributionF(0.0f, DX_TWO_PI_F);
	rot.y = MyRandom::GetDistributionF(0.0f, DX_TWO_PI_F);
	rot.z = MyRandom::GetDistributionF(0.0f, DX_TWO_PI_F);

	// スケールもランダム
	float s = MyRandom::GetDistributionF(0.8f, 1.3f);
	VECTOR scale = {s, s, s};

	return Create(BGOBJECT_CUBE, pos, rot, scale);
}

void BGObjectManager::SetupFloatingMover(BGObject* object)
{
	Floating* mover = ObjectMoverManager::GetInstance()->CreateObjectMover<Floating>();
	object->SetFloatingMover(mover);
	FloatingParam param = {};
	param.width.y = MyRandom::GetDistributionF(2.0f, 3.0f);
	param.speed.y = MyRandom::GetDistributionF(0.005f, 0.01f);
	mover->SetParam(param);
	mover->SetLockZ(true);
	mover->Play();
}
