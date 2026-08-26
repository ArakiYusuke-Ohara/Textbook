#define NOMINMAX
#include "ParticleSystem.h"
#include "DxLib.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>

ParticleSystem::ParticleSystem()
    : defaultRetro_(true), defaultInterval_(3), defaultPixelStep_(1), defaultGravity_(0.15f)
{
}

ParticleSystem::~ParticleSystem() { Clear(); }

void ParticleSystem::SetDefaultRetro(bool enabled, int interval, int pixelStep, float gravity)
{
    defaultRetro_ = enabled;
    defaultInterval_ = std::max(1, interval);
    defaultPixelStep_ = std::max(1, pixelStep);
    defaultGravity_ = gravity;
}

static int RoundToStep(float v, int step)
{
    int r = static_cast<int>(std::round(v));
    if (step <= 1) return r;
    int mod = r % step;
    r -= mod;
    return r;
}

void ParticleSystem::AddExplosion(float x, float y, int count, bool retro, int interval, int pixelStep, float gravity)
{
    bool useRetro = retro;
    int useInterval = interval;
    int usePixelStep = pixelStep;
    float useGravity = gravity;

    if (!retro) {
        useRetro = defaultRetro_;
        useInterval = defaultInterval_;
        usePixelStep = defaultPixelStep_;
        useGravity = defaultGravity_;
    } else {
        useInterval = std::max(1, interval);
        usePixelStep = std::max(1, pixelStep);
    }

    for (int i = 0; i < count; ++i) {
        Particle p;
        p.x = x;
        p.y = y;
        float ang = (static_cast<float>(rand()) / RAND_MAX) * 2.0f * 3.14159265f;
        float spd = 1.0f + (static_cast<float>(rand()) / RAND_MAX) * 3.0f;
        p.vx = cosf(ang) * spd;
        p.vy = sinf(ang) * spd * 0.6f - 1.0f;

        if (useRetro) {
            p.vx = std::round(p.vx);
            p.vy = std::round(p.vy);
            if (p.vx == 0 && (rand() % 2)) p.vx = (rand() % 2) ? 1 : -1;
        }

        // lifetime ~0.25s (assume 60 FPS -> 15 frames). small random variation.
        const int baseLife = 15; // 0.25s @ 60fps
        const int randVar = (rand() % 4); // 0..3 -> 15..18 frames
        p.lifeMax = baseLife + randVar;
        p.life = p.lifeMax;

        p.size = 2 + (rand() % 4);

        // purple-ish
        p.r = 150 + (rand() % 106);
        p.g = 0 + (rand() % 56);
        p.b = 150 + (rand() % 106);

        // per-particle settings
        p.gravity = useGravity;
        p.retro = useRetro;
        p.updateInterval = useInterval;
        p.timer = 0;
        p.pixelStep = usePixelStep;

        particles_.push_back(p);
    }
}

void ParticleSystem::Update()
{
    for (auto &p : particles_) {
        if (p.retro) {
            ++p.timer;
            if (p.timer >= p.updateInterval) {
                p.timer = 0;
                p.x += static_cast<float>(std::round(p.vx));
                p.y += static_cast<float>(std::round(p.vy));
                p.vy += p.gravity;
                --p.life;
                if (p.pixelStep > 1) {
                    p.x = static_cast<float>(RoundToStep(p.x, p.pixelStep));
                    p.y = static_cast<float>(RoundToStep(p.y, p.pixelStep));
                }
            }
        } else {
            p.x += p.vx;
            p.y += p.vy;
            p.vy += p.gravity;
            --p.life;
            if (p.pixelStep > 1) {
                p.x = static_cast<float>(RoundToStep(p.x, p.pixelStep));
                p.y = static_cast<float>(RoundToStep(p.y, p.pixelStep));
            }
        }
    }

    particles_.erase(std::remove_if(particles_.begin(), particles_.end(),
        [](const Particle& p){ return p.life <= 0; }), particles_.end());
}

void ParticleSystem::Draw() const
{
    for (const auto &p : particles_) {
        float t = (p.life / (float)p.lifeMax);
        int r = static_cast<int>(p.r * t);
        int g = static_cast<int>(p.g * t);
        int b = static_cast<int>(p.b * t);
        int half = p.size / 2;
        DrawBox(static_cast<int>(p.x) - half, static_cast<int>(p.y) - half,
                static_cast<int>(p.x) + half, static_cast<int>(p.y) + half,
                GetColor(r, g, b), TRUE);
    }
}

void ParticleSystem::Clear()
{
    particles_.clear();
}