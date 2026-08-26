#include "Player.h"
#include "DxLib.h"
#include <algorithm>
#include <cstdio>

Player::Player()
    : x_(0.0f), y_(0.0f), w_(32), h_(32),
      speed_(4.0f), windowW_(640), windowH_(480),
      fireCooldown_(10), fireTimer_(0),
      playerHandle_(-1), bulletHandle_(-1),
      playerW_(0), playerH_(0), bulletW_(0), bulletH_(0),
      lives_(3), invTimer_(0), invDuration_(60)
{
}

void Player::Init(int windowW, int windowH)
{
    windowW_ = windowW;
    windowH_ = windowH;
    x_ = windowW_ / 2.0f;
    y_ = windowH_ - h_ - 20.0f;
    bullets_.clear();
    fireTimer_ = 0;
    lives_ = 3;
    invTimer_ = 0;

    playerHandle_ = LoadGraph("Data/Player/Player.png");
    if (playerHandle_ != -1) {
        GetGraphSize(playerHandle_, &playerW_, &playerH_);
    } else {
        printf("Warning: Failed to load Data/Player/Player.png\n");
    }

    bulletHandle_ = LoadGraph("Data/Bullet/PlayerBullet.png");
    if (bulletHandle_ != -1) {
        GetGraphSize(bulletHandle_, &bulletW_, &bulletH_);
    } else {
        printf("Warning: Failed to load Data/Bullet/PlayerBullet.png\n");
    }
}

void Player::Update()
{
    // 無敵タイマー減衰
    if (invTimer_ > 0) --invTimer_;

    if (CheckHitKey(KEY_INPUT_LEFT))  x_ -= speed_;
    if (CheckHitKey(KEY_INPUT_RIGHT)) x_ += speed_;

    if (x_ < w_ / 2.0f) x_ = w_ / 2.0f;
    if (x_ > windowW_ - w_ / 2.0f) x_ = windowW_ - w_ / 2.0f;

    // 押下トリガーで単発発射（同時に画面内に存在できる弾は1発まで）
    static bool prevZ = false;
    bool nowZ = (CheckHitKey(KEY_INPUT_Z) != 0);

    if (fireTimer_ > 0) --fireTimer_;
    if (nowZ && !prevZ) {
        if (fireTimer_ == 0) {
            bool hasActive = std::any_of(bullets_.begin(), bullets_.end(),
                                         [](const Bullet& bb){ return bb.active; });
            if (!hasActive) {
                Bullet b;
                b.x = x_;
                b.y = y_ - h_ / 2.0f;
                b.speed = 8.0f;
                b.active = true;
                bullets_.push_back(b);
                fireTimer_ = fireCooldown_;
            }
        }
    }
    prevZ = nowZ;

    for (auto &b : bullets_) {
        if (!b.active) continue;
        b.y -= b.speed;
        if (b.y < -10.0f) b.active = false;
    }

    bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(),
        [](const Bullet& b){ return !b.active; }), bullets_.end());
}

void Player::Draw() const
{
    // 無敵時は軽く点滅（描画スキップで表現）
    bool skipDraw = (invTimer_ > 0) && ((invTimer_ / 6) % 2 == 0);
    if (!skipDraw) {
        if (playerHandle_ != -1 && playerW_ > 0 && playerH_ > 0) {
            DrawGraph((int)(x_ - playerW_ / 2), (int)(y_ - playerH_ / 2), playerHandle_, TRUE);
        } else {
            int left = static_cast<int>(x_ - w_ / 2);
            int top = static_cast<int>(y_ - h_ / 2);
            int right = static_cast<int>(x_ + w_ / 2);
            int bottom = static_cast<int>(y_ + h_ / 2);
            DrawBox(left, top, right, bottom, GetColor(0, 200, 255), TRUE);
        }
    }

    for (const auto &b : bullets_) {
        if (!b.active) continue;
        if (bulletHandle_ != -1 && bulletW_ > 0 && bulletH_ > 0) {
            DrawGraph((int)(b.x - bulletW_ / 2), (int)(b.y - bulletH_ / 2), bulletHandle_, TRUE);
        } else {
            int bx = static_cast<int>(b.x);
            int by = static_cast<int>(b.y);
            DrawBox(bx - 2, by - 6, bx + 2, by + 6, GetColor(255, 255, 0), TRUE);
        }
    }
}

std::vector<Bullet>& Player::GetBullets()
{
    return bullets_;
}

bool Player::TakeHit()
{
    if (invTimer_ > 0) return false; // 無敵中はヒット無効
    --lives_;
    invTimer_ = invDuration_;
    return true;
}

int Player::GetLives() const { return lives_; }
bool Player::IsDead() const { return lives_ <= 0; }
float Player::GetX() const { return x_; }
float Player::GetY() const { return y_; }
float Player::GetHalfW() const { return w_ / 2.0f; }
float Player::GetHalfH() const { return h_ / 2.0f; }

void Player::Fin()
{
    if (playerHandle_ != -1) { DeleteGraph(playerHandle_); playerHandle_ = -1; }
    if (bulletHandle_ != -1) { DeleteGraph(bulletHandle_); bulletHandle_ = -1; }
}