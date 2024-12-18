#pragma once
#include "DxLib.h"

// ヘッダーにインクルードを書きたくないので前方定義
class CollisionAABB;
class CollisionSphere;

// アニメーション
enum PlayerAnimationType
{
	PLAYER_ANIMATION_WALK,
	PLAYER_ANIMATION_JUMP,
	PLAYER_ANIMATION_RANDING,
	PLAYER_ANIMATION_WAIT,
};

// プレイヤークラス
class Player 
{
public:
	Player();	// コンストラクタ
	~Player();	// デストラクタ

public:
	void Init();	// 初期化
	void Load();	// ロード
	void Start();	// 開始
	void Step();	// ステップ
	void Update();	// 更新
	void Draw();	// 描画
	void Fin();		// 終了

public:
	VECTOR GetPos() { return m_Pos; }
	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphereCollision() { return m_SphereCollision; }

public:
	void HitBlock(CollisionAABB* other);
	void HitGoal();

private:
	void PlayAnimation(PlayerAnimationType anim, bool isLoop);
	void UpdateAnimation();

private:
	int m_Handle;	// 画像ハンドル
	int m_AnimationAttachIndex;	// アニメーションのアタッチインデックス
	float m_AnimationTotalTime;	// 再生中のアニメーションの総時間
	float m_AnimationNowTime;	// 再生中のアニメーションの再生時間
	bool m_IsLoopAnimation;		// アニメーションをループさせるか
	PlayerAnimationType m_NowAnimation;	// 再生中のアニメーション
	VECTOR m_Pos;	// 座標
	VECTOR m_Rot;	// 回転
	VECTOR m_Scale;	// スケール
	VECTOR m_Move;	// 移動量
	VECTOR m_PrevPos; // 前回の座標
	CollisionAABB* m_AABB;	// AABBの当たり判定
	CollisionSphere* m_SphereCollision;
	bool m_IsGoal;
};

