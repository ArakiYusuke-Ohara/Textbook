#define NOMINMAX
#include "EnemyManager.h"
#include "DxLib.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>

EnemyManager::EnemyManager()
    : windowW_(640), windowH_(480),
      rows_(3), cols_(8), spacingX_(24), spacingY_(20),
      baseX_(60), baseY_(60),
      groupOffsetX_(0.0f), dir_(1),
      stepX_(8.0f), moveIntervalFrames_(30), moveTimer_(0),
      baseMoveInterval_(30), minMoveInterval_(6), baseStepX_(8.0f), maxStepMultiplier_(1.8f),
      dropY_(8),
      enemyHandle_(-1), enemyW_(32), enemyH_(24),
      enemyBulletHandle_(-1), enemyBulletW_(8), enemyBulletH_(8),
      baseShotInterval_(120), minShotInterval_(20), shotTimer_(0)
{
}

void EnemyManager::Init(int windowW, int windowH)
{
    windowW_ = windowW;
    windowH_ = windowH;

    enemyHandle_ = LoadGraph("Data/Enemy/Enemy.png");
    if (enemyHandle_ != -1) {
        GetGraphSize(enemyHandle_, &enemyW_, &enemyH_);
    } else {
        printf("Info: Enemy image not found at Data/Enemy/Enemy.png; using box.\n");
    }

    // 敵弾画像を読み込む（存在しない場合は矩形フォールバック）
    enemyBulletHandle_ = LoadGraph("Data/Bullet/EnemyBullet.png");
    if (enemyBulletHandle_ != -1) {
        GetGraphSize(enemyBulletHandle_, &enemyBulletW_, &enemyBulletH_);
    } else {
        enemyBulletHandle_ = -1;
        enemyBulletW_ = 8;
        enemyBulletH_ = 8;
    }

    baseMoveInterval_ = moveIntervalFrames_;
    baseStepX_ = stepX_;

    CreateFormation();
    moveTimer_ = 0;
    particleSystem_.Clear();
    enemyBullets_.clear();
    shotTimer_ = 0;
    srand(static_cast<unsigned int>(GetNowCount()));
}

void EnemyManager::CreateFormation()
{
    enemies_.clear();
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            Enemy e;
            e.x = baseX_ + c * (enemyW_ + spacingX_);
            e.y = baseY_ + r * (enemyH_ + spacingY_);
            e.w = enemyW_;
            e.h = enemyH_;
            e.alive = true;
            enemies_.push_back(e);
        }
    }
    groupOffsetX_ = 0.0f;
    dir_ = 1;
}

void EnemyManager::SpawnEnemyBullet(float x, float y)
{
    EnemyBullet b;
    b.x = x;
    b.y = y + (enemyH_ / 2.0f) + (enemyBulletH_ / 2.0f) + 2.0f;
    b.vy = 3.5f;
    b.active = true;
    b.size = enemyBulletW_;
    enemyBullets_.push_back(b);
}

void EnemyManager::Update()
{
    int totalCount = rows_ * cols_;
    int aliveCount = 0;
    for (const auto &e : enemies_) if (e.alive) ++aliveCount;
    float aliveRatio = (totalCount > 0) ? (aliveCount / static_cast<float>(totalCount)) : 0.0f;

    int effectiveInterval = std::max(minMoveInterval_, static_cast<int>(baseMoveInterval_ * aliveRatio));
    float stepMultiplier = 1.0f + (1.0f - aliveRatio) * (maxStepMultiplier_ - 1.0f);
    float effectiveStep = baseStepX_ * stepMultiplier;

    ++moveTimer_;
    if (moveTimer_ >= effectiveInterval) {
        moveTimer_ = 0;
        groupOffsetX_ += dir_ * effectiveStep;

        float left = 1e9f;
        float right = -1e9f;
        for (const auto &e : enemies_) {
            if (!e.alive) continue;
            float ex = e.x + groupOffsetX_;
            left = std::min(left, ex - e.w / 2.0f);
            right = std::max(right, ex + e.w / 2.0f);
        }

        if (left <= right) {
            const int margin = 8;
            if (right >= (windowW_ - margin) && dir_ > 0) {
                float overshoot = right - (windowW_ - margin);
                groupOffsetX_ -= overshoot;
                dir_ = -1;
                for (auto &e : enemies_) e.y += dropY_;
            } else if (left <= margin && dir_ < 0) {
                float overshoot = margin - left;
                groupOffsetX_ += overshoot;
                dir_ = 1;
                for (auto &e : enemies_) e.y += dropY_;
            }
        }
    }

    // 敵の発射（固定間隔）
    ++shotTimer_;
    if (shotTimer_ >= baseShotInterval_) {
        shotTimer_ = 0;
        std::vector<int> aliveIdx;
        for (size_t i = 0; i < enemies_.size(); ++i) {
            if (enemies_[i].alive) aliveIdx.push_back(static_cast<int>(i));
        }
        if (!aliveIdx.empty()) {
            int pick = aliveIdx[rand() % aliveIdx.size()];
            float ex = enemies_[pick].x + groupOffsetX_;
            float ey = enemies_[pick].y;
            SpawnEnemyBullet(ex, ey);
        }
    }

    // 敵弾更新
    for (auto &b : enemyBullets_) {
        if (!b.active) continue;
        b.y += b.vy;
        if (b.y > windowH_ + 16) b.active = false;
    }
    enemyBullets_.erase(std::remove_if(enemyBullets_.begin(), enemyBullets_.end(),
        [](const EnemyBullet& b){ return !b.active; }), enemyBullets_.end());

    // パーティクル更新
    particleSystem_.Update();
}

void EnemyManager::Draw() const
{
    for (const auto &e : enemies_) {
        if (!e.alive) continue;
        int drawX = static_cast<int>(e.x + groupOffsetX_ - e.w / 2);
        int drawY = static_cast<int>(e.y - e.h / 2);
        if (enemyHandle_ != -1) {
            DrawGraph(drawX, drawY, enemyHandle_, TRUE);
        } else {
            DrawBox(drawX, drawY, drawX + e.w, drawY + e.h, GetColor(200, 80, 80), TRUE);
        }
    }

    // 敵弾描画
    for (const auto &b : enemyBullets_) {
        if (!b.active) continue;
        int bx = static_cast<int>(b.x - enemyBulletW_ / 2.0f);
        int by = static_cast<int>(b.y - enemyBulletH_ / 2.0f);
        if (enemyBulletHandle_ != -1) {
            DrawGraph(bx, by, enemyBulletHandle_, TRUE);
        } else {
            DrawBox(bx, by, bx + b.size, by + b.size, GetColor(255, 120, 0), TRUE);
        }
    }

    particleSystem_.Draw();
}

int EnemyManager::CheckBulletCollisions(std::vector<Bullet>& bullets)
{
    int kills = 0;
    const float halfBW = 4.0f;
    const float halfBH = 6.0f;

    for (auto &b : bullets) {
        if (!b.active) continue;
        float bx = b.x;
        float by = b.y;

        bool hit = false;
        for (auto &e : enemies_) {
            if (!e.alive) continue;
            float ex = e.x + groupOffsetX_;
            float ey = e.y;
            float halfEW = e.w / 2.0f;
            float halfEH = e.h / 2.0f;

            if ((bx + halfBW) >= (ex - halfEW) &&
                (bx - halfBW) <= (ex + halfEW) &&
                (by + halfBH) >= (ey - halfEH) &&
                (by - halfBH) <= (ey + halfEH))
            {
                e.alive = false;
                b.active = false;
                ++kills;
                particleSystem_.AddExplosion(ex, ey, 10, true, 6, 1, 0.0f);
                hit = true;
                break;
            }
        }
        if (hit) continue;
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b){ return !b.active; }), bullets.end());

    return kills;
}

int EnemyManager::CheckEnemyBulletHitPlayer(Player& player)
{
    int hits = 0;
    float px = player.GetX();
    float py = player.GetY();
    float halfPW = player.GetHalfW();
    float halfPH = player.GetHalfH();

    for (auto &b : enemyBullets_) {
        if (!b.active) continue;
        float bx = b.x;
        float by = b.y;
        float halfB = b.size / 2.0f;

        if ((bx + halfB) >= (px - halfPW) &&
            (bx - halfB) <= (px + halfPW) &&
            (by + halfB) >= (py - halfPH) &&
            (by - halfB) <= (py + halfPH))
        {
            b.active = false;
            if (player.TakeHit()) ++hits;
        }
    }

    enemyBullets_.erase(std::remove_if(enemyBullets_.begin(), enemyBullets_.end(),
        [](const EnemyBullet& b){ return !b.active; }), enemyBullets_.end());

    return hits;
}

bool EnemyManager::IsClear() const
{
    for (const auto &e : enemies_) {
        if (e.alive) return false;
    }
    return true;
}

void EnemyManager::NextStage()
{
    if (rows_ < 6) rows_ += 1;
    if (cols_ < 12) cols_ += 1;
    if (baseStepX_ < 16.0f) baseStepX_ += 1.0f;
    if (baseMoveInterval_ > 8) baseMoveInterval_ -= 2;
    if (spacingX_ > 8) spacingX_ -= 2;

    moveIntervalFrames_ = baseMoveInterval_;
    stepX_ = baseStepX_;

    particleSystem_.Clear();
    CreateFormation();
}

void EnemyManager::Fin()
{
    if (enemyHandle_ != -1) {
        DeleteGraph(enemyHandle_);
        enemyHandle_ = -1;
    }
    enemies_.clear();
    enemyBullets_.clear();
    particleSystem_.Clear();
}