#pragma once
#include "PlayScene.h"

class NetworkPlayScene : public PlayScene
{
public:
	NetworkPlayScene();
	virtual ~NetworkPlayScene();

public:
	void Init()override;
	void Load()override;
	void Start()override;
	void Step()override;
	void Update()override;
	void Draw()override;
	void Fin()override;
};
