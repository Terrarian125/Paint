#include "DxLib.h"
#include "Input.h" 

// ウィンドウサイズ
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // DxLib初期化
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    if (DxLib_Init() == -1) return -1;

    //描画用のキャンバスを作成
    int canvasHandle = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
    SetDrawScreen(canvasHandle);
    ClearDrawScreen(); // キャンバスを初期化

    // 変数準備
    int drawColor = GetColor(255, 255, 255); // 初期色は白
    int lastX = 0, lastY = 0;               // 前フレームのマウス座標
    int brushSize = 5;                      // ブラシの太さ

    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE)) {
        // 入力情報の更新
        Input::KeyStateUpdate();
        Input::MouseStateUpdate();

        int mouseX = Input::GetMouseX();
        int mouseY = Input::GetMouseY();

        //  カラーパレット設定（1～0キー） 
        if (Input::IsKeyDown(KEY_INPUT_1)) drawColor = GetColor(255, 255, 255); // 白
        if (Input::IsKeyDown(KEY_INPUT_2)) drawColor = GetColor(255, 0, 0);     // 赤
        if (Input::IsKeyDown(KEY_INPUT_3)) drawColor = GetColor(0, 255, 0);     // 緑
        if (Input::IsKeyDown(KEY_INPUT_4)) drawColor = GetColor(0, 0, 255);     // 青
        if (Input::IsKeyDown(KEY_INPUT_5)) drawColor = GetColor(255, 255, 0);   // 黄
        if (Input::IsKeyDown(KEY_INPUT_6)) drawColor = GetColor(255, 0, 255);   // 紫
        if (Input::IsKeyDown(KEY_INPUT_7)) drawColor = GetColor(0, 255, 255);   // 水色
        if (Input::IsKeyDown(KEY_INPUT_8)) drawColor = GetColor(255, 165, 0);   // オレンジ
        if (Input::IsKeyDown(KEY_INPUT_9)) drawColor = GetColor(128, 128, 128); // グレー
        if (Input::IsKeyDown(KEY_INPUT_0)) drawColor = GetColor(50, 50, 50);    // 濃いグレー

        //  描画ロジック 
        // 左クリックで描画、右クリックで消しゴム（黒で塗る）
        bool isLDown = (Input::IsKeepMouseDown(MOUSE_INPUT_LEFT) > 0);
        bool isRDown = (Input::IsKeepMouseDown(MOUSE_INPUT_RIGHT) > 0);

        if (isLDown || isRDown) {
            SetDrawScreen(canvasHandle); // キャンバスに書き込む

            // 消しゴムの場合は黒（背景色）を使う
            int currentBrushColor = isLDown ? drawColor : GetColor(0, 0, 0);

            // 押し始めた瞬間は点、それ以外は前回の座標から線を引く（補間）
            if (Input::IsMouseDown(MOUSE_INPUT_LEFT) || Input::IsMouseDown(MOUSE_INPUT_RIGHT)) {
                DrawCircle(mouseX, mouseY, brushSize, currentBrushColor, TRUE);
            }
            else {
                DrawLine(lastX, lastY, mouseX, mouseY, (brushSize * 2) + 1, currentBrushColor);
                // DrawLineだけだと隙間ができるので円も描く
                DrawCircle(mouseX, mouseY, brushSize, currentBrushColor, TRUE);
            }
            SetDrawScreen(DX_SCREEN_BACK);
        }

        // 座標を保存
        lastX = mouseX;
        lastY = mouseY;

        //  Cキーで全消去 
        if (Input::IsKeyDown(KEY_INPUT_C)) {
            SetDrawScreen(canvasHandle);
            ClearDrawScreen();
            SetDrawScreen(DX_SCREEN_BACK);
        }

        //  画面表示 
        ClearDrawScreen();

        //キャンバスを描画
        DrawGraph(0, 0, canvasHandle, FALSE);

        //カーソルのプレビューを表示（現在の色と太さ）
        DrawCircle(mouseX, mouseY, brushSize, drawColor, isRDown ? FALSE : TRUE);
        if (isRDown) DrawCircle(mouseX, mouseY, brushSize + 1, GetColor(255, 255, 255), FALSE); // 消しゴム時は枠表示

        // UI表示
        DrawFormatString(10, 10, GetColor(255, 255, 255), "1-0: Color  C: Clear  Left: Draw  Right: Erase");

        ScreenFlip();
    }

    DxLib_End();
    return 0;
}