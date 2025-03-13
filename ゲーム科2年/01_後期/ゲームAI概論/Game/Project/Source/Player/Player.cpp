#include "Player.h"
#include "PlayerManager.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Bullet/BulletBase.h"
#include "../Stage/StageParameter.h"
#include "../AI/AIStrategyBase.h"
#include "../AI/AIParameter.h"
#include "../Block/Block.h"

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 40
#define PLAYER_SPEED 2.0f
#define PLAYER_ANIM_GRAPH_NUM 4
#define PLAYER_CHANGE_ANIM_TIME 3
#define PLAYER_CHANGE_DIR_MOVE_DISTANCE 0.1f
#define PLYAER_CHANGE_STRATEGY_TIME 180
#define BLOCK_PUSH_OFFSET 0.1f

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
	m_AnimationIndex = 0;
	m_AnimationTimer = 0;
	m_StrategyTimer = 0;
	m_NowStrategy = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_OldPos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Collision = nullptr;
	m_AIStrategy = nullptr;
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

	// AIがセットされていたらAIのステップ
	if (m_AIStrategy)
	{
		AIStep();
	}
	// AIが無ければ入力操作
	else
	{
		InputMove();
	}
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

	UpdateAnimation();
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

void Player::InputMove()
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

void Player::AIStep()
{
	// 一定時間ごとに行動を切り替える
	if (m_StrategyTimer <= 0)
	{
		// ターゲットを設定
		Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);
		VECTOR player1Pos = player1->GetPos();
		m_AIStrategy->SetTarget(player1Pos);

		// 行動を決定して取得
		m_NowStrategy = m_AIStrategy->ThinkStrategy();

		// タイマーリセット
		m_StrategyTimer = PLYAER_CHANGE_STRATEGY_TIME;
	}

	switch (m_NowStrategy)
	{
		case CPU_STRATEGY_CHASE:	AIChase();	break;
		case CPU_STRATEGY_AWAY:		AIAway();	break;
	}

	m_StrategyTimer--;
}

void Player::AIChase()
{
	// 1Pを追いかける
	Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);
	VECTOR player1Pos = player1->GetPos();
	m_Move = MyMath::VecCreate(m_Pos, player1Pos);
	m_Move = MyMath::VecNormalize(m_Move);
	m_Move = MyMath::VecScale(m_Move, PLAYER_SPEED);

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

void Player::AIAway()
{
	// 1Pから離れる
	Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);
	VECTOR player1Pos = player1->GetPos();
	m_Move = MyMath::VecCreate(m_Pos, player1Pos);
	m_Move = MyMath::VecNormalize(m_Move);
	m_Move = MyMath::VecScale(m_Move, -PLAYER_SPEED);

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
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

	if (m_AnimationTimer >= PLAYER_CHANGE_ANIM_TIME)
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

void Player::HitBlock(Block* block)
{
	// 当たり判定情報を構築
	VECTOR checkPos = m_OldPos;
	CollisionAABB playerCollision;
	playerCollision.SetTargetPos(&checkPos);
	playerCollision.SetSize(m_Collision->GetSize());
	CollisionAABB* blockCollision = block->GetCollision();

	// X軸移動チェックをする
	checkPos.x += m_Move.x;

	if (playerCollision.CheckAABB(blockCollision))
	{
		VECTOR playerSize = playerCollision.GetSize();
		VECTOR blockPos = block->GetPos();
		VECTOR blockSize = blockCollision->GetSize();
		// 左からあたった
		if (m_Move.x > 0.0)
		{
			// 左に押し出す
			checkPos.x -= checkPos.x + playerSize.x - blockPos.x;
		}
		// 右からあたった
		else if (m_Move.x < 0.0f)
		{
			// 右に押し出す
			checkPos.x += blockPos.x + blockSize.x - checkPos.x;
		}
	}

	// Y軸移動チェックをする
	checkPos = m_OldPos;
	checkPos.y += m_Move.y;

	if (playerCollision.CheckAABB(blockCollision))
	{
		VECTOR playerSize = playerCollision.GetSize();
		VECTOR blockPos = block->GetPos();
		VECTOR blockSize = blockCollision->GetSize();
		// 上からあたった
		if (m_Move.y > 0.0)
		{
			// 上に押し出す
			checkPos.y -= checkPos.y + playerSize.y - blockPos.y;
		}
		// 下からあたった
		else if (m_Move.y < 0.0f)
		{
			// 下に押し出す
			checkPos.y += blockPos.y + blockSize.y - checkPos.y;
		}
	}

	// 押し出し後の座標を設定
	m_Pos = checkPos;
}
