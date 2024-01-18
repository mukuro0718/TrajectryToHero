//===========================================================================
//@brief ステージマネージャー/管理
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>

class FarmStage;

class StageManager
{
public:
    StageManager();         // コンストラクタ
    ~StageManager();        //デストラクタ
    void Draw();            //管理するすべてのオブジェクトを描画
    void Update();          //更新
    void Create();     //生成
    void Delete();    //削除
    const int GetModelHandle()const;
private:
    //クラス
    FarmStage* farm;      //マップ
    //変数
    std::vector<int> farmStageData;
};

