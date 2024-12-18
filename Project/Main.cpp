//===========================================================================
//@brief メイン処理
// シーンマネージャーのmain関数を実行する
//===========================================================================
#include"DxLib.h"
#include"SceneManager.h"
#include"Common.h"
#include"FPSController.h"
#include"Load.h"
#include"LoadScene.h"

/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //DXライブラリ初期化処理
    if (DxLib_Init() == -1) { return -1; }

    //画面の作成
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT);
    //フラグを立てることで非同期ロードが可能になる
    SetUseASyncLoadFlag(TRUE);
    //ScreenFlipを実行しても垂直同期信号を待たない
    SetWaitVSyncFlag(FALSE);
    //描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);
    //画面モードをウィンドウモードで描画するか
#if _DEBUG
    ChangeWindowMode(TRUE);
#else
    ChangeWindowMode(FALSE);
#endif// _DEBUG
    SetUseDirect3DVersion(DX_DIRECT3D_9EX);
    //ロードシーンの作成
    LoadScene* loadScene = new LoadScene();
    //ロードインスタンスの生成
    Load::CreateInstance();
    //シーンマネージャーの作成
    SceneManager* sceneManager = new SceneManager();
    //ゲーム本編
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        if (GetASyncLoadNum() == 0)
        {
            sceneManager->mainGame();
        }
        else
        {
            loadScene->Update();
            loadScene->Draw();
        }
    }
    //シーン管理クラスの開放
    if (sceneManager)
    {
        delete(sceneManager);
        sceneManager = nullptr;
    }
    if (loadScene)
    {
        delete(loadScene);
        loadScene = nullptr;
    }

    //DXライブラリの後始末
    DxLib_End();
    //ソフトの終了
    return 0;
}
