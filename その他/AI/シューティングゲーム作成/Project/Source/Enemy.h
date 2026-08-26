#pragma once

struct Enemy {
    float x;
    float y;
    int w;
    int h;
    bool alive;
    int row; // 追加: 敵の行インデックス（0 = 奥/top, rows-1 = 手前）
};