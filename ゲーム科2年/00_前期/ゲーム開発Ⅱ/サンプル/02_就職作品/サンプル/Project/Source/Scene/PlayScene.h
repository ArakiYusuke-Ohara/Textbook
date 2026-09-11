#pragma once
#include "SceneBase.h"

class Floor;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Update() override;
	void Fin() override;
};
