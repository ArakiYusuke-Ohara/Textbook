#include "Player.h"

// コンストラクタ
Player::Player()
{
	// コンストラクタではメンバ変数を0初期化するくらい
	// ややこしい処理はしないこと
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
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
	m_Handle = MV1LoadModel("Resource/Player/Player.x");
}

// 開始
void Player::Start()
{
	// モデルの座標、回転、スケール値を格納する変数
	m_Pos = VGet(0.0f, 1.0f, -3.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
}

// ステップ
void Player::Step()
{
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
}

// 終了
void Player::Fin()
{
	// モデルをメモリから削除
	MV1DeleteModel(m_Handle);
}
