#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "ParticleSystem.h"

struct EnemyBullet {
    float x;
    float y;
    float vy;
    bool active;
    int size;
};

class EnemyManager {
public:
    EnemyManager();
    void Init(int windowW, int windowH);
    void Update();
    void Draw() const;
    void Fin();

    // 弾との当たり判定：倒した敵数を返す（弾は無効化される）
    int CheckBulletCollisions(std::vector<Bullet>& bullets);

    // プレイヤー被弾判定（敵弾 vs プレイヤー）
    int CheckEnemyBulletHitPlayer(Player& player);

    // ステージ制御
    bool IsClear() const;
    void NextStage();

private:
    void CreateFormation();
    void SpawnEnemyBullet(float x, float y);

    int windowW_;
    int windowH_;

    std::vector<Enemy> enemies_;

    // formation settings
    int rows_;
    int cols_;
    int spacingX_;
    int spacingY_;
    float baseX_;
    float baseY_;

    // group motion
    float groupOffsetX_;
    int dir_;
    float stepX_;
    int moveIntervalFrames_;
    int moveTimer_;

    int baseMoveInterval_;
    int minMoveInterval_;
    float baseStepX_;
    float maxStepMultiplier_;

    int dropY_;

    // graphic
    int enemyHandle_;
    int enemyW_;
    int enemyH_;

    // particles (delegated)
    ParticleSystem particleSystem_;

    // enemy bullets (restored)
    std::vector<EnemyBullet> enemyBullets_;
    int enemyBulletHandle_;
    int enemyBulletW_;
    int enemyBulletH_;

    int baseShotInterval_;
    int minShotInterval_;
    int shotTimer_;
};