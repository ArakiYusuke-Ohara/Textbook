#pragma once
#include "Resource.h"

class Model : public Resource
{
public:
	Model();
	virtual ~Model();

	void Load(const char* path);
	void Draw();
	void Fin();

private:
	int m_Handle;
};