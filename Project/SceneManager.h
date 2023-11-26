//===========================================================================
//@brief シーンマネージャークラス
// シーンの各処理を実行する
//===========================================================================

#pragma once
#include"DxLib.h"
#include"Common.h"
class SceneBase;
class FPSController;

class SceneManager final
{
public:
    SceneManager(); //コンストラクタ
    ~SceneManager();//デストラクタ

    void mainGame();//ゲーム本編

private:
    /*内部処理関数*/
    void ChangeScene(); //シーンの切り替え
    void Create();      //作成
    void Final();       //最終処理
    void Update();      //更新
    void Draw();        //描画
    /*クラス*/
    SceneBase*     scene;           //シーン
    FPSController* fpsController;   //FPSコントローラー
};