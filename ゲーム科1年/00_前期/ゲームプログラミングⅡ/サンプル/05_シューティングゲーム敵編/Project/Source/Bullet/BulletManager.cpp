#include "BulletManager.h"
#include "Bullet.h"

void InitAllBullet()
{
	// すべての弾を初期化
	InitBullet();
}

void LoadAllBullet()
{
	// すべての弾をロード
	LoadBullet();
}

void StepAllBullet()
{
	// すべての弾をステップ
	StepBullet();
}

void UpdateAllBullet()
{
	// すべての弾を更新
	UpdateBullet();
}

void DrawAllBullet()
{
	// すべての弾を描画
	DrawBullet();
}

void FinAllBullet()
{
	// すべての弾を終了
	FinBullet();
}

// 弾丸を発射するときはこの関数から呼ぶ
void RequestFireBullet(float posX, float posY, float moveX, float moveY)
{
	// 発射
	FireBullet(posX, posY, moveX, moveY);
}
