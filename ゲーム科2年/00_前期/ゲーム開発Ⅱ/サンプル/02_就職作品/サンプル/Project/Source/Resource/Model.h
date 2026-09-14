#pragma once
#include "Resource.h"

class Model : public Resource
{
public:
	Model();
	virtual ~Model();

	void Load(const char* path);
	void Update();
	void Draw();
	void Fin();

	int GetHandle() const { return m_Handle; }

private:
	int m_Handle;
};