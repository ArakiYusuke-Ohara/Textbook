#include "DxLib.h"
#include "Player.h"
#include "EnemyManager.h"

// ウィンドウサイズ
static const int WINDOW_W = 640;
static const int WINDOW_H = 480;

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    (void)hInstance; (void)hPrevInstance; (void)lpCmdLine; (void)nShowCmd;

    SetGraphMode(WINDOW_W, WINDOW_H, 32);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1) return -1;

    SetDrawScreen(DX_SCREEN_BACK);

    Player player;
    player.Init(WINDOW_W, WINDOW_H);

    EnemyManager enemies;
    enemies.Init(WINDOW_W, WINDOW_H);

    int score = 0;
    int stage = 1;
    int stageClearTimer = 0;
    const int stageClearDuration = 60;
    bool gameOver = false;
    static bool prevZGameOver = false;

    while (ProcessMessage() >= 0)
    {
        ClearDrawScreen();

        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        if (!gameOver) {
            // 更新
            player.Update();
            enemies.Update();

            // プレイヤー弾 vs 敵（Player が管理する弾リストを渡す）
            auto &playerBullets = player.GetBullets();
            int kills = enemies.CheckBulletCollisions(playerBullets);
            if (kills > 0) score += kills;

            // 敵弾 vs プレイヤー（EnemyManager 内の敵弾で判定）
            int enemyHits = enemies.CheckEnemyBulletHitPlayer(player);
            (void)enemyHits; // 必要ならログや効果音処理を追加

            // ステージクリア判定
            if (stageClearTimer == 0 && enemies.IsClear()) {
                stageClearTimer = stageClearDuration;
            }

            // ゲームオーバー判定（被弾結果を確認）
            if (player.IsDead()) {
                gameOver = true;
                prevZGameOver = (CheckHitKey(KEY_INPUT_Z) != 0);
            }
        } else {
            // ゲームオーバー時：Zでリスタート（トリガー）
            bool nowZ = (CheckHitKey(KEY_INPUT_Z) != 0);
            if (nowZ && !prevZGameOver) {
                score = 0;
                stage = 1;
                stageClearTimer = 0;
                gameOver = false;
                player.Init(WINDOW_W, WINDOW_H);
                enemies = EnemyManager();
                enemies.Init(WINDOW_W, WINDOW_H);
                prevZGameOver = false;
            } else {
                prevZGameOver = nowZ;
            }
        }

        // 描画
        player.Draw();
        enemies.Draw();

        DrawFormatString(8, 8, GetColor(255, 255, 255), "SCORE: %d", score);
        DrawFormatString(8, 28, GetColor(255, 255, 255), "STAGE: %d", stage);
        DrawFormatString(8, 48, GetColor(255, 255, 255), "LIVES: %d", player.GetLives());

        if (!gameOver && stageClearTimer > 0) {
            DrawFormatString((WINDOW_W/2) - 60, WINDOW_H/2 - 10, GetColor(255, 255, 0), "STAGE %d CLEAR", stage);
            --stageClearTimer;
            if (stageClearTimer == 0) {
                ++stage;
                enemies.NextStage();
            }
        }

        if (gameOver) {
            DrawFormatString((WINDOW_W/2) - 60, WINDOW_H/2 - 10, GetColor(255, 0, 0), "GAME OVER");
            DrawFormatString((WINDOW_W/2) - 120, WINDOW_H/2 + 10, GetColor(200, 200, 200), "Press Z to restart, ESC to exit");
        }

        ScreenFlip();
    }

    player.Fin();
    enemies.Fin();

    DxLib_End();
    return 0;
}
