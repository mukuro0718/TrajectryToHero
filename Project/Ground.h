//===========================================================================
//@brief 地面クラス/継承
//===========================================================================

#pragma once
#include"DxLib.h"
#include"StageBase.h"

class Ground :public StageBase
{
public:
    Ground() {};                // コンストラクタ
    Ground(int modelHandle);    //引数ありコンストラクタ
    ~Ground();                  //デストラクタ
};

