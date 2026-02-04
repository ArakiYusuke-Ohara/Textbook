#include "Player.h"
#include "PlayerManager.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"
#include "../Bullet/BulletBase.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParameter.h"
#include "../Enemy/EnemyManager.h"
#include "../Enemy/EnemyBase.h"

#define POS_MIN_X		-7.0f
#define POS_MIN_Y		15.0f
#define POS_MAX_X		7.0f
#define POS_MAX_Y		35.0f
#define MOVE_MAX_X		0.16f
#define MOVE_MAX_Y		0.16f
#define MOVE_MAX_Z		0.25f
//#define MOVE_MAX_Z		0.05f
#define BRAKE_X			0.004f
#define BRAKE_Y			0.004f
#define ROTATE_RESILIENCE	0.02f
#define ROTATE_SPEED	0.04f
#define ROTATE_X_MAX	0.4f
#define ROTATE_Y_MAX	0.4f
#define ROTATE_Z_MAX	0.4f
#define NORMAL_BULLET_INTERVAL 12
#define PLAYER_INVISIBLE_TIME 120

// コンストラクタ
Player::Player()
{
	// コンストラクタではメンバ変数を0初期化するくらい
	// ややこしい処理はしないこと
	m_Active = false;
	m_Handle = 0;
	m_NormalCursorHandle = 0;
	m_LockCursorHandle = 0;
	m_NormalBulletId = 0;
	m_NormalBulletInterval = 0;
	m_Hp = 0;
	m_InvisibleTimer = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0, 0.0f, 0.0f);
	m_Accel = VGet(0.0, 0.0f, 0.0f);
	m_Collision = nullptr;
	m_LockEnemy = nullptr;
}

// デストラクタ
Player::~Player()
{
	// 終了処理を呼べば削除した時の後始末忘れを防げる
	Fin();
}

// 初期化
void Player::Init()
{
	BulletManager::GetInstance()->SetupBullet(m_NormalBulletId);
}

// ロード
void Player::Load()
{
	// 3Dモデルをロードする
	m_Handle = MV1LoadModel("Data/Player/Player.x");

	// 通常弾カーソル画像のロード
	m_NormalCursorHandle = LoadGraph("Data/Player/NormalCursor.png");

	// ロックカーソル画像のロード
	m_LockCursorHandle = LoadGraph("Data/Player/LockCursor.png");
}

// 開始
void Player::Start()
{
	m_Active = true;

	// 初期トランスフォーム
	m_Pos = VGet(0.0f, 32.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	// 移動量を初期化
	m_Move = VGet(0.0, 0.0f, 0.0f);
	// 加速度を設定
	m_Accel = VGet(0.008f, 0.008f, 0.0f);

	// くらい判定
	CollisionSphere* collision = CollisionManager::GetInstance()->CreateSphere();
	collision->SetRadius(0.5f);
	collision->SetTargetPos(&m_Pos);
	collision->SetTag(COLLISION_TAG_PLAYER);
	m_Collision = collision;

	// 通常弾のインターバル
	m_NormalBulletInterval = 0;

	// HP
	m_Hp = 3;
}

// ステップ
void Player::Step()
{
	// ベースのZ移動量
	m_Move.z = MOVE_MAX_Z;

	// 上下左右操作
	if (Input::IsInputKey(KEY_LEFT))
	{
		m_Move.x -= m_Accel.x;
		m_Rot.y -= ROTATE_SPEED;
		m_Rot.z += ROTATE_SPEED;
	}
	if (Input::IsInputKey(KEY_RIGHT))
	{
		m_Move.x += m_Accel.x;
		m_Rot.y += ROTATE_SPEED;
		m_Rot.z -= ROTATE_SPEED;
	}
	if (Input::IsInputKey(KEY_UP))
	{
		m_Move.y += m_Accel.y;
		m_Rot.x -= ROTATE_SPEED;
	}
	if (Input::IsInputKey(KEY_DOWN))
	{
		m_Move.y -= m_Accel.y;
		m_Rot.x += ROTATE_SPEED;
	}

	// 移動への抵抗処理
	if (m_Move.x > 0.0f)
	{
		m_Move.x -= BRAKE_X;
		// 抵抗では移動方向を変えない
		m_Move.x = MyMath::MaxF(m_Move.x, 0.0f);
	}
	if (m_Move.x < 0.0f)
	{
		m_Move.x += BRAKE_X;
		// 抵抗では移動方向を変えない
		m_Move.x = MyMath::MinF(m_Move.x, 0.0f);
	}
	if (m_Move.y > 0.0f)
	{
		m_Move.y -= BRAKE_Y;
		// 抵抗では移動方向を変えない
		m_Move.y = MyMath::MaxF(m_Move.y, 0.0f);
	}
	if (m_Move.y < 0.0f)
	{
		m_Move.y += BRAKE_Y;
		// 抵抗では移動方向を変えない
		m_Move.y = MyMath::MinF(m_Move.y, 0.0f);
	}

	// 回転への抵抗処理
	if (m_Rot.x > 0.0f)
	{
		m_Rot.x -= ROTATE_RESILIENCE;
		m_Rot.x = MyMath::MaxF(m_Rot.x, 0.0f);
	}
	if (m_Rot.x < 0.0f)
	{
		m_Rot.x += ROTATE_RESILIENCE;
		m_Rot.x = MyMath::MinF(m_Rot.x, 0.0f);
	}
	if (m_Rot.y > 0.0f)
	{
		m_Rot.y -= ROTATE_RESILIENCE;
		m_Rot.y = MyMath::MaxF(m_Rot.y, 0.0f);
	}
	if (m_Rot.y < 0.0f)
	{
		m_Rot.y += ROTATE_RESILIENCE;
		m_Rot.y = MyMath::MinF(m_Rot.y, 0.0f);
	}
	if (m_Rot.z > 0.0f)
	{
		m_Rot.z -= ROTATE_RESILIENCE;
		m_Rot.z = MyMath::MaxF(m_Rot.z, 0.0f);
	}
	if (m_Rot.z < 0.0f)
	{
		m_Rot.z += ROTATE_RESILIENCE;
		m_Rot.z = MyMath::MinF(m_Rot.z, 0.0f);
	}

	// 移動量の数値キャップ処理
	m_Move.x = MyMath::ClampF(m_Move.x, -MOVE_MAX_X, MOVE_MAX_X);
	m_Move.y = MyMath::ClampF(m_Move.y, -MOVE_MAX_Y, MOVE_MAX_Y);

	// 通常弾
	if (Input::IsInputKey(KEY_Z))
	{
		if (m_NormalBulletInterval <= 0)
		{
			VECTOR bulletVec = VGet(0.0f, 0.0f, 0.0f);
			// ロックしている敵がいる
			if (m_LockEnemy)
			{
				// 敵に向かって発射
				bulletVec = MyMath::VecCreate(m_Pos, m_LockEnemy->GetPos());
			}
			// ロックなしの場合は正面に発射
			else
			{
				bulletVec = CalcBulletVec();
			}

			// 移動方向と同じ向きに発射する(Z位置は0固定)
			VECTOR bulletPos = m_Pos;
			BulletManager::GetInstance()->FireBullet(m_NormalBulletId, bulletPos, bulletVec);

			m_NormalBulletInterval = NORMAL_BULLET_INTERVAL;
		}
	}

	if (m_NormalBulletInterval > 0) m_NormalBulletInterval--;
	if (m_InvisibleTimer > 0)m_InvisibleTimer--;

	// ロックする敵を検索
	SearchLockEnemy();
}

// 更新
void Player::Update()
{
	// 移動量を反映
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	// 移動範囲
	m_Pos.x = MyMath::ClampF(m_Pos.x, POS_MIN_X, POS_MAX_X);
	m_Pos.y = MyMath::ClampF(m_Pos.y, POS_MIN_Y, POS_MAX_Y);

	// 回転範囲
	m_Rot.x = MyMath::ClampF(m_Rot.x, -ROTATE_X_MAX, ROTATE_X_MAX);
	m_Rot.y = MyMath::ClampF(m_Rot.y, -ROTATE_Y_MAX, ROTATE_Y_MAX);
	m_Rot.z = MyMath::ClampF(m_Rot.z, -ROTATE_Z_MAX, ROTATE_Z_MAX);

	// 3Dモデルの座標を設定する(Z座標は0で固定。周りを動かさせる)
	MV1SetPosition(m_Handle, VGet(m_Pos.x, m_Pos.y, 0.0f));
	// 3Dモデルの回転値を設定する
	MV1SetRotationXYZ(m_Handle, m_Rot);
	// 3Dモデルのスケールを設定する
	MV1SetScale(m_Handle, m_Scale);
}

// 描画
void Player::Draw()
{
	// 無敵中は点滅
	if (IsInvisible())
	{
		if (m_InvisibleTimer % 4 == 0)
		{
			// 3Dモデルを描画する
			MV1DrawModel(m_Handle);
		}
	}
	else
	{
		// 3Dモデルを描画する
		MV1DrawModel(m_Handle);
	}

	// ロックしている場合はロックカーソル
	if (m_LockEnemy)
	{
		VECTOR pos = PlayerManager::GetInstance()->ConvertPlayerLocalPos(m_LockEnemy->GetPos());
		pos = ConvWorldPosToScreenPos(pos);
		DrawRotaGraph((int)pos.x, (int)pos.y, 1.0, 0.0f, m_LockCursorHandle, TRUE);
	}
	// ロックしてない場合は通常カーソル
	else
	{
		VECTOR bulletVec = CalcBulletVec();
		VECTOR targetVec = MyMath::VecScale(bulletVec, 10.0f);
		VECTOR playerPos = VGet(m_Pos.x, m_Pos.y, 0.0f);
		VECTOR targetPos = MyMath::VecAdd(playerPos, targetVec);
		DrawBillboard3D(targetPos, 0.5f, 0.5f, 1.0f, 0.0f, m_NormalCursorHandle, TRUE);
	}

	// 座標を描画する
	DrawFormatString(0, 0, GetColor(0, 0, 0), "座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}

// 終了
void Player::Fin()
{
	// 画像削除
	MV1DeleteModel(m_Handle);
	DeleteGraph(m_NormalCursorHandle);
	DeleteGraph(m_LockCursorHandle);
}

void Player::HitEnemyBullet(BulletBase* bullet)
{
	m_InvisibleTimer = PLAYER_INVISIBLE_TIME;

	int damage = bullet->GetDamage();
	m_Hp -= damage;

	EffekseerManager::GetInstance()->PlayEffect3D(EFFEKSEER_PLAYER_DAMAGE, bullet->GetPos());
}

void Player::Dead()
{
	m_Active = false;
	m_Collision->SetActive(false);
}

VECTOR Player::CalcBulletVec()
{
	VECTOR result = MyMath::VecScale(m_Move, 0.4f);
	result.z = 1.0f;

	result = MyMath::VecNormalize(result);
	return result;
}

void Player::SearchLockEnemy()
{
	// 前回のロックオンを覚えておく
	EnemyBase* prevLockEnemy = m_LockEnemy;

	// 見つからなければロック解除
	m_LockEnemy = nullptr;

	float matchMax = 0.0f;
	auto enemyList = EnemyManager::GetInstance()->GetEnemyList();
	for (EnemyBase* enemy : enemyList)
	{
		if (!enemy->IsActive()) continue;

		// 一定距離近くないとロックしない
		VECTOR enemyPos = enemy->GetPos();
		if ((enemyPos.z - m_Pos.z) <= 100.0f)
		{
			// 敵までのベクトルを計算して正規化
			VECTOR enemyVec = MyMath::VecCreate(m_Pos, enemyPos);
			enemyVec = MyMath::VecNormalize(enemyVec);

			// 正規化された弾の軌道ベクトルを取得
			VECTOR bulletLine = CalcBulletVec();

			// 正規化された2つのベクトルの内積を計算すると
			// どれだけ合わさっているかが0～1.0でわかる
			float dot = MyMath::VecDot(enemyVec, bulletLine);

			// 合わさっている度が一定以上で一番よく合わさっているエネミーをロック
			if (dot >= 0.99f)
			{
				if (dot > matchMax)
				{
					m_LockEnemy = enemy;
					matchMax = dot;
				}
			}

		}
	}

	// 新しくロックオンした場合はエフェクトを表示
	if (m_LockEnemy && m_LockEnemy != prevLockEnemy)
	{
		VECTOR pos = PlayerManager::GetInstance()->ConvertPlayerLocalPos(m_LockEnemy->GetPos());
		pos = ConvWorldPosToScreenPos(pos);
		EffekseerManager::GetInstance()->PlayEffect2D(EFFEKSEER_PLAYER_LOCK_ON, pos);
	}
}
