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

    const void mainGame();//ゲーム本編

private:
    /*内部処理関数*/
    const void ChangeScene(); //シーンの切り替え
    const void Create();      //作成
    const void Final();       //最終処理
    const void Update();      //更新
    const void Draw();        //描画
    /*クラス*/
    SceneBase*     scene;           //シーン
    FPSController* fpsController;   //FPSコントローラー
};