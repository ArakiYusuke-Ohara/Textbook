#pragma once

#include "DxLib.h"

class ObjectMoverBase
{
public:
	ObjectMoverBase();
	virtual~ObjectMoverBase();

public:
	virtual void Play();
	virtual void Update() = 0;

public:
	bool IsActive() const { return m_Active; }

	void SetActive(bool active) { m_Active = active; }
	void SetObjectPos(VECTOR* objectPos) { m_ObjectPos = objectPos; }

protected:
	bool m_Active;
	VECTOR* m_ObjectPos;
};
