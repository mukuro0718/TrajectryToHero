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

    const void Draw(const bool _isFarm);    //管理するすべてのオブジェクトを描画
    const void Update(const int _playerLv); //更新
    const void Create();                    //生成
    const void Delete();                    //削除
    
    /*getter*/
    const VECTOR GetBonfirePos()const;
    const VECTOR GetGatePos()const;
    const bool   GetIsShowGate()const;
    const int    GetModelHandle()const;
private:
    /*メンバ変数*/
    FarmStage*  farm;   //マップ
    Bonfire*    bonfire;//かがり火

    std::vector<int> farmStageData;//ステージモデルデータ
};

