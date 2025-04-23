#include "PlayerBase.h"
#include "PlayerManager.h"
#include "PlayerParameter.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BulletParameter.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Bullet/BulletBase.h"
#include "../Stage/StageParameter.h"
#include "../Stage/StageManager.h"
#include "../Stage/Stage.h"
#include "../Block/Block.h"
#include "../Item/Item.h"
#include "../Item/ItemParameter.h"

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 40
#define PLAYER_ANIM_GRAPH_NUM 4
#define PLAYER_CHANGE_ANIM_TIME 3
#define PLAYER_CHANGE_DIR_MOVE_DISTANCE 0.1f
#define BLOCK_PUSH_OFFSET 0.1f
#define ATTACK_STIFFNESS 40
#define DAMAGE_INVISIBLE_TIME 240
#define DEFAULT_MOVE_SPEED 1.0f
#define DEFAULT_BULLET_INTERVAL 180



const VECTOR BULLET_FIRE_DIR[] =
{
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{-1.0f, 0.0f, 0.0f},
	{0.0f, -1.0f, 0.0f},
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

const BulletID USE_BULLET[] =
{
	BULLET_ID_PLAYER1,
	BULLET_ID_PLAYER2,
	BULLET_ID_PLAYER3,
	BULLET_ID_PLAYER4,
};

// コンストラクタ
PlayerBase::PlayerBase()
{
	m_Active = false;
	m_Handle = 0;
	m_Hp = 0;
	m_InvisibleTimer = 0;
	m_BulletInterval = 0;
	m_BulletIntervalTime = 0;
	m_PlayerNumber = 0;
	m_Direction = 0;
	m_AnimationIndex = 0;
	m_AnimationTimer = 0;
	m_UseBulletID = 0;
	m_Stiffness = 0;
	m_MoveSpeed = 0.0f;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_OldPos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_CollisionAABB = nullptr;
	m_CollisionSphere = nullptr;
}

// デストラクタ
PlayerBase::~PlayerBase()
{
	Fin();
}

// 初期化
void PlayerBase::Init()
{
	// 使用する弾丸
	m_UseBulletID = USE_BULLET[m_PlayerNumber];

	// 弾丸をセットアップ
	BulletManager::GetInstance()->SetupBullet(m_UseBulletID);
}

// ロード
void PlayerBase::Load()
{
	m_Handle = LoadGraph(PLAYER_GRAPHIC_PATH[m_PlayerNumber]);
}

// 開始
void PlayerBase::Start()
{
	m_Active = true;

	Stage* stage = StageManager::GetInstance()->GetStage();
	float stagePosX = stage->GetPosX();
	float stagePosY = stage->GetPosY();

	// 初期トランスフォーム
	m_Pos = MyMath::VecAdd(VGet(stagePosX, stagePosY, 0.0f), DEFAULT_POS[m_PlayerNumber]);
	// 移動量を初期化
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// 当たり判定(AABB)
	CollisionAABB* aabb = CollisionManager::GetInstance()->CreateAABB();
	aabb->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));
	aabb->SetTargetPos(&m_Pos);
	aabb->SetTag(COLLISION_TAG[m_PlayerNumber]);
	m_CollisionAABB = aabb;

	// 当たり判定(円)
	CollisionSphere* sphere = CollisionManager::GetInstance()->CreateSphere();
	sphere->SetRadius(20.0f);
	sphere->SetTargetPos(&m_Pos);
	sphere->SetTag(COLLISION_TAG[m_PlayerNumber]);
	m_CollisionSphere = sphere;

	// 通常弾のインターバル
	m_BulletInterval = 0;
	m_BulletIntervalTime = DEFAULT_BULLET_INTERVAL;

	// HP
	m_Hp = 3;

	// 向き
	m_Direction = PLAYER_DIRECTION_DOWN;

	// 移動速度
	m_MoveSpeed = DEFAULT_MOVE_SPEED;
}

// ステップ
void PlayerBase::Step()
{
	m_OldPos = m_Pos;

	// バレットインターバール
	if (m_BulletInterval > 0) m_BulletInterval--;
	// 硬直
	if (m_Stiffness > 0)m_Stiffness--;
	// 無敵時間
	if (m_InvisibleTimer > 0)m_InvisibleTimer--;

}

// 更新
void PlayerBase::Update()
{
	UpdateAnimation();
}

// 描画
void PlayerBase::Draw()
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
void PlayerBase::Fin()
{
	// 画像削除
	DeleteGraph(m_Handle);
}

void PlayerBase::FireBullet()
{
	// インターバル中は撃てない
	if (IsBulletInterval()) return;

	// 少し前方に発射
	VECTOR move = BULLET_FIRE_DIR[m_Direction];
	VECTOR offset = MyMath::VecScale(move, 10.0f);
	VECTOR pos = MyMath::VecAdd(m_Pos, offset);
	BulletManager::GetInstance()->FireBullet(m_UseBulletID, pos, move);

	// インターバルと硬直
	m_BulletInterval = m_BulletIntervalTime;
	m_Stiffness = ATTACK_STIFFNESS;
}

void PlayerBase::Dead()
{
	m_Active = false;
	m_CollisionAABB->SetActive(false);
}


void PlayerBase::UpdateAnimation()
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

void PlayerBase::HitBlock(Block* block)
{
	// 当たり判定情報を構築
	VECTOR checkPos = m_OldPos;
	CollisionAABB playerCollision;
	playerCollision.SetTargetPos(&checkPos);
	playerCollision.SetSize(m_CollisionAABB->GetSize());
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

void PlayerBase::HitBullet()
{
	m_InvisibleTimer = DAMAGE_INVISIBLE_TIME;
}

void PlayerBase::HitItem(Item* item)
{
	const ItemParameter* itemParam = item->GetParam();

	switch (itemParam->id)
	{
	case ITEM_ID_PLAYER_SPEED_UP:
		m_MoveSpeed += itemParam->value;
		break;

	case ITEM_ID_BULLET_RAPID_UP:
		m_BulletIntervalTime -= (int)(itemParam->value);
		break;

	case ITEM_ID_BULLET_SPEED_UP:
		break;
	}
}

void PlayerBase::SetDirectionForMove()
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
