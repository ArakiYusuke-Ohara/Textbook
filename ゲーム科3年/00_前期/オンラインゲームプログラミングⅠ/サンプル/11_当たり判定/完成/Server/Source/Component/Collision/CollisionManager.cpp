#include "CollisionManager.h"
#include "CollisionParameter.h"
#include "ColliderComponent.h"
#include "../../Object/GameObject.h"
#include "DxLib.h"

void CollisionManager::Draw()
{
#ifdef _DEBUG
    // 登録されているコライダーを描画
    for (auto col : m_Colliders)
    {
        col->Draw();
	}
#endif
}

/// <summary>
/// コライダーをマネージャーに登録
/// </summary>
/// <param name="col">登録するコライダー</param>
void CollisionManager::Register(ColliderComponent* col)
{
    // nullptrガード
    if (!col) return;

    // 多重登録の防止
    auto it = std::find(m_Colliders.begin(), m_Colliders.end(), col);
    if (it != m_Colliders.end())
        return;  // すでに登録済みなら何もしない

    m_Colliders.push_back(col);
}

/// <summary>
/// 登録されたコライダーを解除
/// </summary>
/// <param name="col">解除したいコライダー</param>
void CollisionManager::Unregister(ColliderComponent* col)
{
    // nullptrガード
    if (!col) return;

    // 見つけて削除
    auto it = std::find(m_Colliders.begin(), m_Colliders.end(), col);
    if (it != m_Colliders.end())
    {
        m_Colliders.erase(it);
    }
}

/// <summary>
/// 当たり判定
/// </summary>
void CollisionManager::CheckCollision()
{
    // コライダーに対して当たり判定＆押し出し
    const size_t size = m_Colliders.size();

    // 全コライダー総当たり
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            ColliderComponent* a = m_Colliders[i];
            ColliderComponent* b = m_Colliders[j];

            CollisionResult result = a->CheckCollide(*b);

            // 当たっていたら押し出し
            if (result.isHit)
            {
                if (result.overlapX <= result.overlapY)
                {
					a->GetOwner()->Move(VGet( result.normalX * result.overlapX * 0.5f, 0.0f, 0.0f));
                    b->GetOwner()->Move(VGet(-result.normalX * result.overlapX * 0.5f, 0.0f, 0.0f));
                }
                else
                {
                    a->GetOwner()->Move(VGet(0.0f,  result.normalY * result.overlapY * 0.5f, 0.0f));
                    b->GetOwner()->Move(VGet(0.0f, -result.normalY * result.overlapY * 0.5f, 0.0f));
                }
            }
        }
    }
}
