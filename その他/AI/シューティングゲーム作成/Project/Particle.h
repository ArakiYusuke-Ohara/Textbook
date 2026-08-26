#pragma once
#include <vector>

struct Particle {
    float x, y;
    float vx, vy;
    int life;
    int lifeMax;
    int size;
    int r, g, b;
};

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();

    // 炎上エフェクトを追加（x,y: 中心）
    void AddExplosion(float x, float y, int count = 12);

    // フレーム毎の更新・描画
    void Update();
    void Draw() const;

    // 全リソースクリア
    void Clear();

private:
    std::vector<Particle> particles_;
};