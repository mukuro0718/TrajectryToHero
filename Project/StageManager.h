//===========================================================================
//@brief ステージマネージャー/管理
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>

class FarmStage;
class Bonfire;

class StageManager
{
public:
    StageManager();   // コンストラクタ
    ~StageManager();  //デストラクタ
    void Draw(const bool _isFarm);      //管理するすべてのオブジェクトを描画
    void Update(const int _playerLv);    //更新
    void Create();    //生成
    void Delete();    //削除
    const int GetModelHandle()const;
    const VECTOR GetBonfirePos()const;
    const bool GetIsShowGate()const;
    const VECTOR GetGatePos()const;
private:
    //クラス
    FarmStage* farm;    //マップ
    Bonfire* bonfire;   //かがり火
    //変数
    std::vector<int> farmStageData;
};

