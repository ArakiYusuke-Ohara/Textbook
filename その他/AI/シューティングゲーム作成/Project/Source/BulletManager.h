#pragma once
#include <vector>

struct ManagedBullet {
    float x;
    float y;
    float vx;
    float vy;
    bool active;
    bool fromPlayer; // true = player bullet, false = enemy bullet
    int size;        // fallback size
};

class BulletManager {
public:
    static BulletManager& Instance();

    void Init(); // Load graphics if any (call after DxLib_Init)
    void Fin();

    // Fire bullets
    void FirePlayer(float x, float y, float speedY); // speedY typically negative (up)
    void FireEnemy(float x, float y, float speedY);  // positive (down)

    // Update / Draw
    void Update();
    void Draw() const;

    // Access all bullets (caller filters by fromPlayer)
    std::vector<ManagedBullet>& GetBullets();

    void ClearAll();

private:
    BulletManager();
    ~BulletManager();

    std::vector<ManagedBullet> bullets_;

    // optional graphics
    int playerBulletHandle_;
    int enemyBulletHandle_;
    int playerBulletW_;
    int playerBulletH_;
    int enemyBulletW_;
    int enemyBulletH_;
};