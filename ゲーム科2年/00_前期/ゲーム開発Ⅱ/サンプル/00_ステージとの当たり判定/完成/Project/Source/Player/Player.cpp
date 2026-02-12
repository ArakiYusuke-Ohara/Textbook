#include "Player.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Stage/Stage.h"

#define ROTATION_SPEED	0.1f
#define MOVE_SPEED		0.1f
#define JUMP_POW		0.3f
#define GRAVITY			0.020f


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
	m_OldPos = VGet(0.0, 0.0f, 0.0f);
	m_AABB = nullptr;
	m_SphereCollision = nullptr;
	m_IsGoal = false;
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
	m_Pos = VGet(0.0f, 2.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	// 移動量を初期化
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// AABBの当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));

	// 球の当たり判定を設定
	m_SphereCollision = CollisionManager::GetInstance()->CreateSphere();
	m_SphereCollision->SetTargetPos(&m_Pos);
	m_SphereCollision->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	m_SphereCollision->SetRadius(0.8f);

	// ゴールフラグを折る
	m_IsGoal = false;
}

// ステップ
void Player::Step()
{
	// XY移動量は毎フレームリセット
	m_Move = VGet(0.0, m_Move.y, 0.0f);

	// 左右で回転
	if (Input::IsInputKey(KEY_LEFT))
	{
		// Y軸回転
		m_Rot.y -= ROTATION_SPEED;
	}
	if (Input::IsInputKey(KEY_RIGHT))
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
	if (Input::IsInputKey(KEY_UP))
	{
		// 前方ベクトルを取得
		VECTOR front = MyMath::VecForwardZX(m_Rot.y);
		// 前方ベクトルに速度を掛けたものが移動量となる
		front = MyMath::VecScale(front, MOVE_SPEED);
		m_Move.x = front.x;
		m_Move.z = front.z;
	}

	// Zキーでジャンプ
	if (Input::IsTriggerKey(KEY_Z))
	{
		m_Move.y = JUMP_POW;
	}

	// 重力
	m_Move.y -= GRAVITY;

	// 移動前の座標を記録
	m_OldPos = m_Pos;

	// 移動量を反映
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

// 更新
void Player::Update()
{
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

	// ゴールしたら文字を表示
	if (m_IsGoal)
	{
		DrawString(0, 40, "ゴールした！！", GetColor(255, 255, 255));
	}
}

// 終了
void Player::Fin()
{
	// モデルをメモリから削除
	MV1DeleteModel(m_Handle);
}

void Player::CheckStage(Stage* stage)
{
	MV1_COLL_RESULT_POLY_DIM hitResult = stage->CheckCollisionSphere(m_SphereCollision->GetWorldPos(), m_SphereCollision->GetRadius());
	if (hitResult.HitNum <= 0) return;

	float playerRadius = m_SphereCollision->GetRadius();

	// まずは壁から
	// 衝突したポリゴンの数だけループ
	for (int i = 0; i < hitResult.HitNum; i++)
	{
		// 当たったポリゴンを抽出
		MV1_COLL_RESULT_POLY polygon = hitResult.Dim[i];
		// 壁の法線のY成分が0.1未満であれば床か天井なので無視
		float normalY = polygon.Normal.y > 0.0f ? polygon.Normal.y : -polygon.Normal.y;
		if (normalY > 0.1f) continue;

		// 移動ベクトルと向かい合ったベクトルとだけ衝突処理をする
		VECTOR moveNormal = MyMath::VecNormalize(m_Move);
		if (MyMath::VecDot(moveNormal, polygon.Normal) > 0.0f) continue;

		// 移動ベクトルと壁の法線ベクトルの外積を計算する
		VECTOR move = VGet(m_Move.x, 0.0f, m_Move.z);
		VECTOR slideVec = MyMath::VecCross3D(move, polygon.Normal);

		// 壁の法線ベクトルとslideVecの外積が壁沿いベクトルとなる
		slideVec = MyMath::VecCross3D(polygon.Normal, slideVec);
		slideVec.y = m_Move.y;

		// 移動前の座標から壁沿いベクトルを加算した場所が
		// 壁押し出し後の座標となる
		m_Pos = MyMath::VecAdd(m_OldPos, slideVec);

		// まだ他の壁に当たってないかチェックする
		bool isHit = false;
		for (int i = 0; i < hitResult.HitNum; i++)
		{
			MV1_COLL_RESULT_POLY p = hitResult.Dim[i];

			float nY = p.Normal.y > 0.0f ? p.Normal.y : -p.Normal.y;
			if (nY > 0.1f) continue;

			if (HitCheck_Sphere_Triangle(m_SphereCollision->GetWorldPos(), m_SphereCollision->GetRadius(),
				p.Position[0], p.Position[1], p.Position[2]))
			{
				// 他の壁に当たっている場合は壁の法線の向きに押し出す
				VECTOR slideVec = MyMath::VecScale(p.Normal, 0.2f);
				m_Pos = MyMath::VecAdd(m_Pos, slideVec);
				isHit = true;
				break;
			}
		}

		if (!isHit)
		{
			break;
		}
	}

	// ここから床

	for (int i = 0; i < hitResult.HitNum; i++)
	{
		// 当たったポリゴンを抽出
		MV1_COLL_RESULT_POLY polygon = hitResult.Dim[i];

		// 法線のY成分が0.1以下の場合は壁なので無視
		if (polygon.Normal.y <= 0.1f) continue;

		// 中心から足元にラインを引き当たり判定を取る
		VECTOR lineStart = m_SphereCollision->GetWorldPos();	// 球の当たり判定の中心座標
		VECTOR lineEnd = m_Pos;									// プレイヤーの足元の座標

		HITRESULT_LINE lineResult = HitCheck_Line_Triangle(lineStart, lineEnd, 
			polygon.Position[0], polygon.Position[1], polygon.Position[2]);

		// ラインに何も当たらなければ次のポリゴンへ
		if (!lineResult.HitFlag) continue;

		// ラインに当たった座標の高さにY座標を合わせる
		m_Pos.y = lineResult.Position.y;

		// 着地処理
		m_Move.y = 0.0f;
	}

	MV1SetPosition(m_Handle, m_Pos);

	// ヒット結果は削除する必要がある
	MV1CollResultPolyDimTerminate(hitResult);
}

void Player::HitBlock(CollisionAABB* other)
{
	// 移動前の座標に設定する
	m_Pos = m_OldPos;
	MV1SetPosition(m_Handle, m_Pos);
}

void Player::HitGoal()
{
	m_IsGoal = true;
}
