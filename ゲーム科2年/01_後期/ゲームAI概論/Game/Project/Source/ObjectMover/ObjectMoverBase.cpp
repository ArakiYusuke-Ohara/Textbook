#include "ObjectMoverBase.h"

ObjectMoverBase::ObjectMoverBase()
{
	m_Active = false;
	m_ObjectPos = nullptr;
}

ObjectMoverBase::~ObjectMoverBase()
{
}

void ObjectMoverBase::Play()
{
	m_Active = true;
}



