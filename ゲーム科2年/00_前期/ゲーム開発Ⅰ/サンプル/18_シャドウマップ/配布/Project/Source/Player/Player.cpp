#include "Player.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Scene/SceneManager.h"

#define ROTATION_SPEED	0.1f
#define MOVE_SPEED		0.1f
#define ANIMATION_SPEED 1.0f

// コンストラクタ
Player::Player()
{
	// コンストラクタではメンバ変数を0初期化するくらい
	// ややこしい処理はしないこと
	m_Handle = 0;
	m_AnimationAttachIndex = 0;
	m_AnimationTotalTime = 0.0f;
	m_AnimationNowTime = 0.0f;
	m_IsLoopAnimation = false;
	m_NowAnimation = PLAYER_ANIMATION_WALK;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0, 0.0f, 0.0f);
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
	m_Handle = MV1LoadModel("Data/Player/CubeRobot.x");
}

// 開始
void Player::Start()
{
	// モデルの座標、回転、スケール値を格納する変数
	m_Pos = VGet(0.0f, 0.0f, -3.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	// 移動量を初期化
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// ゴールフラグを折る
	m_IsGoal = false;

	// 待機アニメーションを再生
	PlayAnimation(PLAYER_ANIMATION_WAIT, true);
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
		// 歩行アニメーション再生
		PlayAnimation(PLAYER_ANIMATION_WALK, true);
	}
	else
	{
		// 歩いていなければ待機アニメーションに戻す
		PlayAnimation(PLAYER_ANIMATION_WAIT, true);
	}
}

// 更新
void Player::Update()
{
	// 移動前の座標を記録
	m_PrevPos = m_Pos;

	// 移動量を反映
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	// 3Dモデルの座標を設定する
	MV1SetPosition(m_Handle, m_Pos);
	// 3Dモデルの回転値を設定する
	MV1SetRotationXYZ(m_Handle, m_Rot);
	// 3Dモデルのスケールを設定する
	MV1SetScale(m_Handle, m_Scale);

	// アニメーションを更新する
	UpdateAnimation();
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

void Player::PlayAnimation(PlayerAnimationType anim, bool isLoop)
{
	// 再生中のアニメーションで呼ばれた場合は何もしない
	if (anim == m_NowAnimation) return;

	// 再生していたアニメーションはデタッチする
	MV1DetachAnim(m_Handle, m_AnimationAttachIndex);

	// アニメーションをアタッチする
	m_AnimationAttachIndex = MV1AttachAnim(m_Handle, anim);

	// アニメーションのトータル時間を取得
	m_AnimationTotalTime = MV1GetAttachAnimTotalTime(m_Handle, m_AnimationAttachIndex);

	// 現在の再生時間を0にする
	m_AnimationNowTime = 0.0f;

	// ループ設定
	m_IsLoopAnimation = isLoop;

	// 再生中のアニメーション設定
	m_NowAnimation = anim;
}

void Player::UpdateAnimation()
{
	// アニメーションの再生時間を設定
	MV1SetAttachAnimTime(m_Handle, m_AnimationAttachIndex, m_AnimationNowTime);

	// 再生時間を進める
	m_AnimationNowTime += ANIMATION_SPEED;

	// 末尾まで再生したか
	if (m_AnimationNowTime > m_AnimationTotalTime)
	{
		// ループ設定なら冒頭へ戻す
		if (m_IsLoopAnimation)
		{
			m_AnimationNowTime = 0.0f;
		}
		// ループでなければ末尾で止める
		else
		{
			m_AnimationNowTime = m_AnimationTotalTime;
		}
	}
}