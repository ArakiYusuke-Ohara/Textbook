#include <windows.h>       // Windows API の基本ヘッダ
#include <d3d11.h>         // Direct3D 11 のヘッダ
#pragma comment(lib, "d3d11.lib")  // Direct3D 11 のライブラリをリンク

// グローバル変数（Direct3Dの主要オブジェクト）
HWND g_hWnd = nullptr;                        // ウィンドウハンドル
ID3D11Device* g_pd3dDevice = nullptr;         // デバイス本体（GPUとのインターフェース）
ID3D11DeviceContext* g_pImmediateContext = nullptr; // 描画コマンドを発行するコンテキスト
IDXGISwapChain* g_pSwapChain = nullptr;       // フロント/バックバッファを切り替えるスワップチェイン
ID3D11RenderTargetView* g_pRenderTargetView = nullptr; // 描画先（バックバッファ）へのビュー

// Direct3D の初期化関数
bool InitD3D(HWND hWnd) {
    // スワップチェインの設定
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;                                // バッファ数（1つのバックバッファ）
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // カラーフォーマット
    scd.BufferDesc.Width = 1600;                         // 幅（ウィンドウサイズと一致）
    scd.BufferDesc.Height = 900;                        // 高さ
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // バッファの用途（描画先）
    scd.OutputWindow = hWnd;                            // 出力先のウィンドウ
    scd.SampleDesc.Count = 1;                           // アンチエイリアスの設定（なし）
    scd.Windowed = TRUE;                                // ウィンドウモード（フルスクリーンじゃない）

    // デバイス、コンテキスト、スワップチェインの作成
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,                        // アダプター（nullptr = 自動選択）
        D3D_DRIVER_TYPE_HARDWARE,      // ハードウェアアクセラレーション
        nullptr, 0,                     // ソフトウェア・フラグ
        nullptr, 0,                     // 機能レベルの指定（デフォルト）
        D3D11_SDK_VERSION,             // SDK バージョン
        &scd,                          // スワップチェイン設定
        &g_pSwapChain,                 // 出力：スワップチェイン
        &g_pd3dDevice,                 // 出力：デバイス
        nullptr,                       // 出力：使用された機能レベル（不要）
        &g_pImmediateContext           // 出力：デバイスコンテキスト
    );

    if (FAILED(hr)) return false;

    // バックバッファを取得
    ID3D11Texture2D* pBackBuffer = nullptr;
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // バックバッファからレンダーターゲットビューを作成
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
    pBackBuffer->Release(); // バックバッファの参照カウントを減らす（ビューを使うので不要）

    // レンダーターゲットをコンテキストに設定
    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);

    // ビューポートの設定（描画範囲）
    D3D11_VIEWPORT vp = {};
    vp.Width = 1600;
    vp.Height = 900;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports(1, &vp);

    return true;
}

// Direct3Dのリソース解放
void CleanD3D() {
    if (g_pRenderTargetView) g_pRenderTargetView->Release();
    if (g_pSwapChain) g_pSwapChain->Release();
    if (g_pImmediateContext) g_pImmediateContext->Release();
    if (g_pd3dDevice) g_pd3dDevice->Release();
}

// 毎フレーム描画する関数
void RenderFrame() {
    // 背景色（RGBA）：青色
    float color[4] = { 0.0f, 0.4f, 0.8f, 1.0f };

    // 描画ターゲット（バックバッファ）をクリア
    g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, color);

    // バックバッファをフロントバッファに表示（垂直同期あり）
    g_pSwapChain->Present(1, 0);
}

// ウィンドウプロシージャ（メッセージ処理）
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_DESTROY) {
        PostQuitMessage(0); // ウィンドウが閉じられたら終了メッセージを送る
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam); // デフォルト処理
}

// アプリケーションのエントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    // ウィンドウクラスの登録
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"DXWindowClass";
    RegisterClass(&wc);

    // ウィンドウの作成
    g_hWnd = CreateWindow(wc.lpszClassName, L"DirectX11 サンプル",
        WS_OVERLAPPEDWINDOW, 100, 100, 1600, 900,
        nullptr, nullptr, hInstance, nullptr);

    ShowWindow(g_hWnd, nCmdShow); // ウィンドウ表示

    // Direct3D 初期化
    if (!InitD3D(g_hWnd)) return 0;

    // メインループ（終了メッセージが来るまで繰り返す）
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            RenderFrame(); // 毎フレーム描画
        }
    }

    // 終了処理（リソース解放）
    CleanD3D();
    return 0;
}
