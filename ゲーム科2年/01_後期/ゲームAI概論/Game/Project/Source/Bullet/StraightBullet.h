#pragma once

#include "BulletBase.h"

class StraightBullet : public BulletBase
{
public:
	StraightBullet();
	~StraightBullet();

public:
	void Step() override;
	void Update() override;
	void Draw() override;
	BulletBase* Clone() override;
};
