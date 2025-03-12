#pragma once

class Stage
{
public:
	Stage();
	~Stage();

public:
	void Load();
	void Draw();
	void Fin();

private:
	int m_Handle;
};