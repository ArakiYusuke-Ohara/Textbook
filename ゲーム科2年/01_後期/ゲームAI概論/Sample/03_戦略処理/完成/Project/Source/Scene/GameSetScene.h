#pragma once
#include "SceneBase.h"

class UIImage;

class GameSetScene : public SceneBase
{
public:
	GameSetScene();
	~GameSetScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;
};
