#include "ObjectMoverManager.h"
#include "ObjectMoverParameter.h"
#include "ObjectMoverBase.h"
#include <typeinfo>


const EaseInOutParam EASE_IN_OUT_MASTER_PARAM[] =
{
	{ {-4.0f, 35.0f, 0.0f}, {-40.0f, 80.0f, 0.0f},   60, 180, 60 },
	{ { -1.0f, 35.0f, 0.0f }, {-10.0f, 80.0f, 0.0f}, 60, 180, 60 },
	{ { 1.0f, 35.0f, 0.0f }, {10.0f, 80.0f, 0.0f},   60, 180, 60 },
	{ { 4.0f, 35.0f, 0.0f}, {40.0f, 80.0f, 0.0f},    60, 180, 60 },
	{ {-4.0f, 25.0f, 0.0f}, {-40.0f, 30.0f, 0.0f},   60, 180, 60 },
	{ { -1.0f, 25.0f, 0.0f }, {-40.0f, 30.0f, 0.0f}, 60, 180, 60 },
	{ { 1.0f, 25.0f, 0.0f }, {40.0f, 30.0f, 0.0f},   60, 180, 60 },
	{ { 4.0f, 25.0f, 0.0f}, {40.0f, 30.0f, 0.0f},    60, 180, 60 },
	{ {-4.0f, 15.0f, 0.0f}, {-40.0f, -10.0f, 0.0f},  60, 180, 60 },
	{ { -1.0f, 15.0f, 0.0f }, {-10.0f, -10.0f, 0.0f},60, 180, 60 },
	{ { 1.0f, 15.0f, 0.0f }, {10.0f, -10.0f, 0.0f},  60, 180, 60 },
	{ { 4.0f, 15.0f, 0.0f}, {-40.0f, -10.0f, 0.0f},  60, 180, 60 },
};

ObjectMoverManager::ObjectMoverManager()
{
}

ObjectMoverManager::~ObjectMoverManager()
{
	Fin();
}

void ObjectMoverManager::Fin()
{
	for (ObjectMoverBase* mover : m_Moveres)
	{
		delete mover;
	}

	m_Moveres.clear();
}

const EaseInOutParam* ObjectMoverManager::GetEaseInOutParam(int id)
{
	return &EASE_IN_OUT_MASTER_PARAM[id];
}
