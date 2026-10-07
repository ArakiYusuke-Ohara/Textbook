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

	int Duplicate() const;

private:
	int m_Handle;
};