//===========================================================================
//@brief ステージベースクラス
//===========================================================================
#pragma once
#include "DxLib.h"
class StageBase
{
public:
	StageBase(){}						// コンストラクタ
	StageBase(int _modelHandle);			// 引数ありコンストラクタ
	virtual ~StageBase();				// デストラクタ

	void Draw();						//描画
	void Delete();						//最終処理
	void Update();						//更新
	const int GetModelHandle()const { return modelHandle; }

protected:
	//定数
	static const VECTOR SCALE;			//拡大率
	static const VECTOR INIT_STAGE_POS;//初期プレイヤー座標
	//変数
	VECTOR pos;							//ポジション
	int modelHandle;					//モデルハンドル
};

