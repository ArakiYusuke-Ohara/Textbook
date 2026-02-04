#pragma once
#include "DxLib.h"
#include "CameraBase.h"

// カメラクラス
class PlayCamera : public CameraBase
{
public:
	PlayCamera();	// コンストラクタ
	~PlayCamera();	// デストラクタ

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;
};


