#pragma once
#include <vector>

struct Particle {
    float x, y;
    float vx, vy;
    int life;
    int lifeMax;
    int size;
    int r, g, b;

    // per-particle settings
    float gravity;      // this particle's gravity (can be 0)
    bool retro;         // retro discrete movement flag
    int updateInterval; // frames between updates when retro==true
    int timer;          // per-particle timer
    int pixelStep;      // snap positions to this grid when >1
};

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();

    // AddExplosion:
    // x,y: center, count: number of particles
    // retro: whether this explosion uses discrete retro movement
    // interval: frames between discrete moves (used when retro==true)
    // pixelStep: snap positions to multiples of this value (1 = no snap)
    // gravity: per-particle gravity (0 for no gravity)
    void AddExplosion(float x, float y, int count = 12, bool retro = false,
                      int interval = 3, int pixelStep = 1, float gravity = 0.15f);

    void Update();
    void Draw() const;
    void Clear();

    // global default for newly created particles (used if retro arg not provided)
    void SetDefaultRetro(bool enabled, int interval = 3, int pixelStep = 1, float gravity = 0.15f);

private:
    std::vector<Particle> particles_;

    // global defaults
    bool defaultRetro_;
    int defaultInterval_;
    int defaultPixelStep_;
    float defaultGravity_;
};