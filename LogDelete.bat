@echo off
chcp 65001 >nul

rem ユーザーに対象ディレクトリを入力させる
set /p "TARGET_DIR=削除対象のディレクトリを入力してください: "

rem 入力されたディレクトリが存在するか確認
if not exist "%TARGET_DIR%" (
    echo 入力されたディレクトリが存在しません。処理を終了します。
    pause
    exit /b
)

rem 指定したディレクトリ以下のLog.txtを検索して削除する
for /r "%TARGET_DIR%" %%f in (Log.txt) do (
    echo 削除中: %%f
    del /f /q "%%f"
)

echo 全てのLog.txtを削除しました。
pause
