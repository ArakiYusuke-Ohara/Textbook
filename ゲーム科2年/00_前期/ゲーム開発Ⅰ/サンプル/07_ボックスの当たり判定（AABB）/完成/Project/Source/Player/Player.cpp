#include "Player.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Block/BlockManager.h"
#include "../Block/Block.h"

#define ROTATION_SPEED	0.03f
#define MOVE_SPEED		0.03f
#define PLAYER_WIDTH	1.0f
#define PLAYER_HEIGHT	1.0f
#define PLAYER_DEPTH	1.0f

// コンストラクタ
Player::Player()
{
	// コンストラクタではメンバ変数を0初期化するくらい
	// ややこしい処理はしないこと
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0, 0.0f, 0.0f);
	m_AABB = nullptr;
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
}

// ロード
void Player::Load()
{
	// 3Dモデルをロードする
	m_Handle = MV1LoadModel("Data/Player/Player.x");
}

// 開始
void Player::Start()
{
	// モデルの座標、回転、スケール値を格納する変数
	m_Pos = VGet(0.0f, 1.0f, -3.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	// 移動量を初期化
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// 当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	m_AABB->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_DEPTH));
}

// ステップ
void Player::Step()
{
	// 移動量は毎フレームリセット
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// 左右で回転
	if (Input::IsInputKey(Input::KEY_LEFT))
	{
		// Y軸回転
		m_Rot.y -= ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_RIGHT))
	{
		// Y軸回転
		m_Rot.y += ROTATION_SPEED;
	}

	// 回転値のキャップ処理(0～2πの値にする)
	if (m_Rot.y < 0.0f)
	{
		m_Rot.y += DX_TWO_PI_F;
	}
	else if (m_Rot.y > DX_TWO_PI_F)
	{
		m_Rot.y -= DX_TWO_PI_F;
	}

	// 上キーで前進
	if (Input::IsInputKey(Input::KEY_UP))
	{
		// 前方ベクトルを取得
		VECTOR front = MyMath::VecForwardZX(m_Rot.y);
		// 前方ベクトルに速度を掛けたものが移動量となる
		m_Move = MyMath::VecScale(front, MOVE_SPEED);
	}
}

// 更新
void Player::Update()
{
	// 当たり判定付き移動
	MoveWithCollision();

	// 3Dモデルの座標を設定する
	MV1SetPosition(m_Handle, m_Pos);
	// 3Dモデルの回転値を設定する
	MV1SetRotationXYZ(m_Handle, m_Rot);
	// 3Dモデルのスケールを設定する
	MV1SetScale(m_Handle, m_Scale);
}

// 描画
void Player::Draw()
{
	// 3Dモデルを描画する
	MV1DrawModel(m_Handle);

	// 座標を描画する
	DrawFormatString(0, 0, GetColor(255, 255, 255), "座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);

	// 回転値を描画する
	DrawFormatString(0, 20, GetColor(255, 255, 255), "回転[%f, %f, %f]", m_Rot.x, m_Rot.y, m_Rot.z);
}

// 終了
void Player::Fin()
{
	// モデルをメモリから削除
	MV1DeleteModel(m_Handle);
}

void Player::MoveWithCollision()
{
	// X軸だけプレイヤーを移動させる
	m_Pos.x += m_Move.x;

	// ブロックと当たり判定
	HitResultAABB hitResult = CheckHitBlocks();
	if (hitResult.isHit)
	{
		// 左からあたったか
		if (m_Move.x > 0.0f)
		{
			// 左に押し出す
			m_Pos.x -= m_AABB->GetRight() - hitResult.hitLeft;
		}
		// 右からあたったか
		else if (m_Move.x < 0.0f)
		{
			// 右に押し出す
			m_Pos.x += hitResult.hitRight - m_AABB->GetLeft();
		}

		// 移動量は0にする
		m_Move.x = 0.0f;
	}

	// Y軸だけプレイヤーを移動させる
	m_Pos.y += m_Move.y;

	// ブロックと当たり判定
	hitResult = CheckHitBlocks();
	if (hitResult.isHit)
	{
		// 上からあたったか
		if (m_Move.y < 0.0f)
		{
			// 上に押し出す
			m_Pos.y += hitResult.hitTop - m_AABB->GetBottom();
		}
		// 下からあたったか
		else if (m_Move.y > 0.0f)
		{
			// 下に押し出す
			m_Pos.y -= m_AABB->GetTop() - hitResult.hitBottom;
		}

		// 移動量は0にする
		m_Move.y = 0.0f;
	}

	// Z軸だけプレイヤーを移動させる
	m_Pos.z += m_Move.z;

	// ブロックと当たり判定
	hitResult = CheckHitBlocks();
	if (hitResult.isHit)
	{
		// 手前からあたったか
		if (m_Move.z > 0.0f)
		{
			// 手前に押し出す
			m_Pos.z -= m_AABB->GetBack() - hitResult.hitFront;
		}
		// 奥からあたったか
		else if (m_Move.z < 0.0f)
		{
			// 奥に押し出す
			m_Pos.z += hitResult.hitBack - m_AABB->GetFront();
		}
		// 移動量は0にする
		m_Move.z = 0.0f;
	}
}

HitResultAABB Player::CheckHitBlocks()
{  
   Block* block = BlockManager::GetInstance()->GetBlocks();  
   for (int i = 0; i < BLOCK_MAX; i++, block++)  
   {  
	   CollisionAABB* blockAABB = block->GetAABB();
	   const HitResultAABB result = m_AABB->CheckAABB(blockAABB);
	   if (result.isHit)
	   {
		   // 当たった
		   return result;
	   }
   }

   return HitResultAABB();
}
