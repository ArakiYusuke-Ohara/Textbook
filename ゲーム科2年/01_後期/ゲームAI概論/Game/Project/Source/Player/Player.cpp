#include "Player.h"
#include "PlayerManager.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Bullet/BulletBase.h"
#include "../Stage/StageParameter.h"

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 40
#define PLAYER_SPEED 2.0f
#define PLAYER_ANIM_GRAPH_NUM 4
#define PLAYER_CHANGE_ANIM_TIMER 3
#define PLAYER_CHANGE_DIR_MOVE_DISTANCE 0.1f

enum PlayerDirection
{
	PLAYER_DIRECTION_RIGHT,
	PLAYER_DIRECTION_DOWN,
	PLAYER_DIRECTION_LEFT,
	PLAYER_DIRECTION_UP,
};

const char* PLAYER_GRAPHIC_PATH[] =
{
	"Data/Play/Player/Player1.png",
	"Data/Play/Player/Player2.png",
	"Data/Play/Player/Player3.png",
	"Data/Play/Player/Player4.png",

};

const VECTOR DEFAULT_POS[] =
{
	{40.0f, 40.0f, 0.0f},
	{560.0f, 40.0f, 0.0f},
};

const CollisionTag COLLISION_TAG[] =
{
	COLLISION_TAG_PLAYER1,
	COLLISION_TAG_PLAYER2,
	COLLISION_TAG_PLAYER3,
	COLLISION_TAG_PLAYER4,
};

// コンストラクタ
Player::Player()
{
	m_Active = false;
	m_Handle = 0;
	m_Hp = 0;
	m_InvisibleTimer = 0;
	m_BulletInterval = 0;
	m_PlayerNumber = 0;
	m_Direction = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_OldPos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Collision = nullptr;
}

// デストラクタ
Player::~Player()
{
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
	m_Handle = LoadGraph(PLAYER_GRAPHIC_PATH[m_PlayerNumber]);
}

// 開始
void Player::Start()
{
	m_Active = true;

	// 初期トランスフォーム
	m_Pos = MyMath::VecAdd(VGet(STAGE_POS_X, STAGE_POS_Y, 0.0f), DEFAULT_POS[m_PlayerNumber]);
	// 移動量を初期化
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// 当たり判定
	CollisionAABB* collision = CollisionManager::GetInstance()->CreateAABB();
	collision->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));
	collision->SetLocalPos(VGet(20.0f, 20.0f, 0.0f));
	collision->SetTargetPos(&m_Pos);
	collision->SetTag(COLLISION_TAG[m_PlayerNumber]);
	m_Collision = collision;

	// 通常弾のインターバル
	m_BulletInterval = 0;

	// HP
	m_Hp = 3;

	// 向き
	m_Direction = PLAYER_DIRECTION_DOWN;
}

// ステップ
void Player::Step()
{
	m_OldPos = m_Pos;

	// AIがセットされていたらAIの移動
	if (m_AIStrategy)
	{
		AIMove();
	}
	// 入力操作移動
	else
	{
		Move();
	}

	UpdateAnimation();
}

// 更新
void Player::Update()
{
	// 移動前の座標から向きを決定
	VECTOR moveVec = MyMath::VecCreate(m_OldPos, m_Pos);

	// 移動量が少なすぎたら向きを変えない
	if (MyMath::VecLong(moveVec) < PLAYER_CHANGE_DIR_MOVE_DISTANCE)return;

	// XとY大きい方を優先
	if (MyMath::Absolute(moveVec.x) > MyMath::Absolute(moveVec.y))
	{
		if (moveVec.x > 0.0f)
		{
			m_Direction = PLAYER_DIRECTION_RIGHT;
		}
		else
		{
			m_Direction = PLAYER_DIRECTION_LEFT;
		}
	}
	else
	{
		if (moveVec.y > 0.0f)
		{
			m_Direction = PLAYER_DIRECTION_DOWN;
		}
		else
		{
			m_Direction = PLAYER_DIRECTION_UP;
		}
	}
}

// 描画
void Player::Draw()
{
	// 無敵中は点滅
	if (IsInvisible())
	{
		if (m_InvisibleTimer % 4 == 0)
		{
			// 描画
			DrawRectGraph((int)m_Pos.x, (int)m_Pos.y,
				m_AnimationIndex * PLAYER_WIDTH, m_Direction * PLAYER_HEIGHT, 
				PLAYER_WIDTH, PLAYER_HEIGHT,
				m_Handle, TRUE);

		}
	}
	else
	{
		// 描画
		DrawRectGraph((int)m_Pos.x, (int)m_Pos.y,
			m_AnimationIndex * PLAYER_WIDTH, m_Direction * PLAYER_HEIGHT,
			PLAYER_WIDTH, PLAYER_HEIGHT,
			m_Handle, TRUE);
	}
}

// 終了
void Player::Fin()
{
	// 画像削除
	DeleteGraph(m_Handle);
}

void Player::Dead()
{
	m_Active = false;
	m_Collision->SetActive(false);
}

void Player::Move()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	if (Input::IsInputKey(KEY_UP))
	{
		m_Move.y = -1.0f;
	}
	else if (Input::IsInputKey(KEY_DOWN))
	{
		m_Move.y = 1.0f;
	}
	else if (Input::IsInputKey(KEY_LEFT))
	{
		m_Move.x = -1.0f;
	}
	else if (Input::IsInputKey(KEY_RIGHT))
	{
		m_Move.x = 1.0f;
	}

	// 移動ベクトルを移動速度の大きさにする
	m_Move = MyMath::VecNormalize(m_Move);
	m_Move = MyMath::VecScale(m_Move, PLAYER_SPEED);

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

void Player::AIMove()
{
}

void Player::UpdateAnimation()
{
	// 移動していなければ0コマ目で停止
	if (MyMath::VecLong(m_Move) <= 0)
	{
		m_AnimationTimer = 0;
		m_AnimationIndex = 0;
		return;
	}

	if (m_AnimationTimer >= PLAYER_CHANGE_ANIM_TIMER)
	{
		m_AnimationTimer = 0;
		m_AnimationIndex++;
		if (m_AnimationIndex >= PLAYER_ANIM_GRAPH_NUM)
		{
			m_AnimationIndex = 0;
		}

	}
	m_AnimationTimer++;
}
