#pragma once
#include <vector>

struct Bullet {
    float x;
    float y;
    float speed;
    bool active;
};

class Player {
public:
    Player();
    void Init(int windowW, int windowH);
    void Update();
    void Draw() const;
    void Fin();

    // 弾への参照（当たり判定用）
    std::vector<Bullet>& GetBullets();

    // 当たり判定 / ライフ管理
    bool TakeHit();         // 被弾処理：無敵中は false を返す。ダメージを受けて残機が減ると true。
    int GetLives() const;
    bool IsDead() const;

    // 位置情報アクセス
    float GetX() const;
    float GetY() const;
    float GetHalfW() const;
    float GetHalfH() const;

private:
    float x_;
    float y_;
    int w_;
    int h_;
    float speed_;
    int windowW_;
    int windowH_;

    std::vector<Bullet> bullets_;
    int fireCooldown_;
    int fireTimer_;

    int playerHandle_;
    int bulletHandle_;
    int playerW_;
    int playerH_;
    int bulletW_;
    int bulletH_;

    // ライフと無敵
    int lives_;
    int invTimer_;
    int invDuration_; // frames
};