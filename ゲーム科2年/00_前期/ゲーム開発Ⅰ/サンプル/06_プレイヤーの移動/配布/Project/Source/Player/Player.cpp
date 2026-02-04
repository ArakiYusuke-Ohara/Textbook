#include "Player.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"

#define ROTATION_SPEED	0.1f
#define MOVE_SPEED		0.1f


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

}

// ステップ
void Player::Step()
{
	// 移動量は毎フレームリセット
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// 左右で回転
	if (Input::IsInputKey(Input::KEY_LEFT))
	{


	}
	if (Input::IsInputKey(Input::KEY_RIGHT))
	{


	}

	// 回転値のキャップ処理(0～2πの値にする)
	if (m_Rot.y < 0.0f)
	{

	}
	else if (m_Rot.y > DX_TWO_PI_F)
	{

	}

	// 上キーで前進
	if (Input::IsInputKey(Input::KEY_UP))
	{
		// 前方ベクトルを取得


		// 前方ベクトルに速度を掛けたものが移動量となる

	}
}

// 更新
void Player::Update()
{
	// 移動量を反映
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

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
