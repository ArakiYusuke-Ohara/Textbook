#pragma once
#include "UIBase.h"

class UIImage : public UIBase
{
public:
	UIImage();
	~UIImage();

public:
	void Load(const char* path);
	void Draw();
	void Fin();

private:
	int m_Handle;
};