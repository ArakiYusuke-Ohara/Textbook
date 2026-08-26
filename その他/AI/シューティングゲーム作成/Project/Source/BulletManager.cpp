#define NOMINMAX
#include "BulletManager.h"
#include "DxLib.h"
#include <algorithm>
#include <cstdio>

BulletManager& BulletManager::Instance() {
    static BulletManager inst;
    return inst;
}

BulletManager::BulletManager()
    : playerBulletHandle_(-1), enemyBulletHandle_(-1),
      playerBulletW_(0), playerBulletH_(0), enemyBulletW_(0), enemyBulletH_(0)
{
}

BulletManager::~BulletManager() { Fin(); }

void BulletManager::Init()
{
    playerBulletHandle_ = LoadGraph("Data/Bullet/PlayerBullet.png");
    if (playerBulletHandle_ != -1) {
        GetGraphSize(playerBulletHandle_, &playerBulletW_, &playerBulletH_);
    } else {
        printf("Info: Player bullet image not found at Data/Bullet/PlayerBullet.png\n");
        playerBulletHandle_ = -1;
        playerBulletW_ = 4; playerBulletH_ = 8;
    }

    enemyBulletHandle_ = LoadGraph("Data/Bullet/EnemyBullet.png");
    if (enemyBulletHandle_ != -1) {
        GetGraphSize(enemyBulletHandle_, &enemyBulletW_, &enemyBulletH_);
    } else {
        printf("Info: Enemy bullet image not found at Data/Bullet/EnemyBullet.png\n");
        enemyBulletHandle_ = -1;
        enemyBulletW_ = 6; enemyBulletH_ = 6;
    }
}

void BulletManager::Fin()
{
    ClearAll();
    if (playerBulletHandle_ != -1) { DeleteGraph(playerBulletHandle_); playerBulletHandle_ = -1; }
    if (enemyBulletHandle_ != -1) { DeleteGraph(enemyBulletHandle_); enemyBulletHandle_ = -1; }
}

void BulletManager::ClearAll()
{
    bullets_.clear();
}

void BulletManager::FirePlayer(float x, float y, float speedY)
{
    ManagedBullet b;
    b.x = x;
    b.y = y;
    b.vx = 0.0f;
    b.vy = speedY;
    b.active = true;
    b.fromPlayer = true;
    b.size = playerBulletW_ > 0 ? playerBulletW_ : 4;
    bullets_.push_back(b);
}

void BulletManager::FireEnemy(float x, float y, float speedY)
{
    ManagedBullet b;
    b.x = x;
    b.y = y;
    b.vx = 0.0f;
    b.vy = speedY;
    b.active = true;
    b.fromPlayer = false;
    b.size = enemyBulletW_ > 0 ? enemyBulletW_ : 6;
    bullets_.push_back(b);
}

void BulletManager::Update()
{
    for (auto &b : bullets_) {
        if (!b.active) continue;
        b.x += b.vx;
        b.y += b.vy;
        if (b.y < -64 || b.y > 1024) b.active = false;
    }
    bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
        [](const ManagedBullet& b){ return !b.active; }), bullets_.end());
}

void BulletManager::Draw() const
{
    for (const auto &b : bullets_) {
        if (!b.active) continue;
        if (b.fromPlayer) {
            if (playerBulletHandle_ != -1) {
                int dx = static_cast<int>(b.x - playerBulletW_ / 2.0f);
                int dy = static_cast<int>(b.y - playerBulletH_ / 2.0f);
                DrawGraph(dx, dy, playerBulletHandle_, TRUE);
            } else {
                int bx = static_cast<int>(b.x - b.size/2);
                int by = static_cast<int>(b.y - b.size/2);
                DrawBox(bx, by, bx + b.size, by + b.size, GetColor(255,255,0), TRUE);
            }
        } else {
            if (enemyBulletHandle_ != -1) {
                int dx = static_cast<int>(b.x - enemyBulletW_ / 2.0f);
                int dy = static_cast<int>(b.y - enemyBulletH_ / 2.0f);
                DrawGraph(dx, dy, enemyBulletHandle_, TRUE);
            } else {
                int bx = static_cast<int>(b.x - b.size/2);
                int by = static_cast<int>(b.y - b.size/2);
                DrawBox(bx, by, bx + b.size, by + b.size, GetColor(255,120,0), TRUE);
            }
        }
    }
}

std::vector<ManagedBullet>& BulletManager::GetBullets()
{
    return bullets_;
}