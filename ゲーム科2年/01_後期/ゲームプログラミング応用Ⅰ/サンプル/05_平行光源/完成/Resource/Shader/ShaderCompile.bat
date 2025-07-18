@echo off
setlocal enabledelayedexpansion
cd /d "%~dp0"

set COMPILER=ShaderCompiler.exe
set OUTPUT_DIR=..\..\Project\Data\Shader
set LOG_FILE=compile_log.txt

if exist "%LOG_FILE%" del "%LOG_FILE%"
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

echo ==== コンパイル開始: %DATE% %TIME% ==== >> "%LOG_FILE%"

for %%f in (*.hlsl) do (
    set FILE=%%~nxf
    set NAME=%%~nf
    set TARGET=

    echo. >> "%LOG_FILE%"
    echo 処理中: !FILE! >> "%LOG_FILE%"

    echo !FILE! | find /i "_vs.hlsl" >nul
    if not errorlevel 1 (
        set TARGET=vs_2_0
    ) else (
        echo !FILE! | find /i "_ps.hlsl" >nul
        if not errorlevel 1 (
            set TARGET=ps_2_0
        )
    )

    if defined TARGET (
        echo コンパイルコマンド: %COMPILER% /T !TARGET! "!FILE!" >> "%LOG_FILE%"
        "%COMPILER%" "!FILE!" /T!TARGET! >> "%LOG_FILE%" 2>&1
        if exist "!NAME!.pso" (
            move /Y "!NAME!.pso" "%OUTPUT_DIR%"
            echo 出力ファイル移動: !NAME!.pso >> "%LOG_FILE%"
        )
        if exist "!NAME!.vso" (
            move /Y "!NAME!.vso" "%OUTPUT_DIR%"
            echo 出力ファイル移動: !NAME!.vso >> "%LOG_FILE%"
        )
        if exist "!NAME!.fx" (
            move /Y "!NAME!.fx" "%OUTPUT_DIR%"
            echo 出力ファイル移動: !NAME!.fx >> "%LOG_FILE%"
        )
    ) else (
        echo スキップ: !FILE!（_vs または _ps を含まれていません） >> "%LOG_FILE%"
    )
)

echo ==== コンパイル完了: %DATE% %TIME% ==== >> "%LOG_FILE%"
echo ログは %LOG_FILE% を参照してください。

echo.
echo コンパイル処理が完了しました。  
echo ログファイル "%LOG_FILE%" を開いてエラーなどを確認してください。  
pause
