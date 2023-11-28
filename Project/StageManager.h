//===========================================================================
//@brief ステージマネージャー/管理
//===========================================================================

#pragma once
#include"DxLib.h"
#include"StageBase.h"

class StageManager
{
public:
    StageManager();         // コンストラクタ
    ~StageManager();        //デストラクタ
    void Draw();            //管理するすべてのオブジェクトを描画
    void Update();          //更新
    void CreateStage();     //生成
    void DestroyStage();    //削除
    const int GetModelHandle()const { return ground->GetModelHandle(); }
private:
    //クラス
    StageBase* ground;      //マップ
    //変数
    int model;
};

