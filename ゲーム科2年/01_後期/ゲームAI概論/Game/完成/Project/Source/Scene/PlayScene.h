#pragma once
#include "SceneBase.h"

class UIImage;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

private:
	bool IsGameSet();

private:
	UIImage* m_UIBG;
};
