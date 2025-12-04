#include "CollisionManager.h"
#include "CollisionParameter.h"
#include "ColliderComponent.h"
#include "../../Object/GameObject.h"
#include "DxLib.h"

void CollisionManager::Register(ColliderComponent* col)
{
    // nullptrƒK[ƒh
    if (!col) return;

    // ‘½d“o˜^‚Ì–h~
    auto it = std::find(m_Colliders.begin(), m_Colliders.end(), col);
    if (it != m_Colliders.end())
        return;  // ‚·‚Å‚É“o˜^Ï‚İ‚È‚ç‰½‚à‚µ‚È‚¢

    m_Colliders.push_back(col);
}

void CollisionManager::Unregister(ColliderComponent* col)
{
    // nullptrƒK[ƒh
    if (!col) return;

    // Œ©‚Â‚¯‚Äíœ
    auto it = std::find(m_Colliders.begin(), m_Colliders.end(), col);
    if (it != m_Colliders.end())
    {
        m_Colliders.erase(it);
    }
}

void CollisionManager::CheckCollision()
{
    const size_t size = m_Colliders.size();

    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            ColliderComponent* a = m_Colliders[i];
            ColliderComponent* b = m_Colliders[j];

            CollisionResult result = a->IsCollide(*b);

            // “–‚½‚Á‚Ä‚¢‚½‚ç‰Ÿ‚µo‚µ
            if (result.isHit)
            {
                if (result.overlapX != 0.0f)
                {
					a->GetOwner()->Move(VGet( result.normalX * result.overlapX * 0.5f, 0.0f, 0.0f));
                    b->GetOwner()->Move(VGet(-result.normalX * result.overlapX * 0.5f, 0.0f, 0.0f));
                }
                else if (result.overlapY != 0.0f)
                {
                    a->GetOwner()->Move(VGet(0.0f,  result.normalY * result.overlapY, 0.0f));
                    b->GetOwner()->Move(VGet(0.0f, -result.normalY * result.overlapY, 0.0f));
                }
            }
        }
    }
}
