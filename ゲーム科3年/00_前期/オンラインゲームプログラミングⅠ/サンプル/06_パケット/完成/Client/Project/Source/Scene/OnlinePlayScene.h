#pragma once
#include "PlayScene.h"

class OnlinePlayScene : public PlayScene
{
public:
	OnlinePlayScene();
	virtual ~OnlinePlayScene();

public:
	void Init()override;
	void Load()override;
	void Start()override;
	void Step()override;
	void Update()override;
	void Draw()override;
	void Fin()override;
};
