//===========================================================================
//@brief ステージベースクラス
//===========================================================================
#pragma once
#include "DxLib.h"
#include<vector>
class StageBase
{
public:
	StageBase(std::vector<int> _data);			// 引数ありコンストラクタ
	virtual ~StageBase();				// デストラクタ

	void Draw();						//描画
	void Delete();						//最終処理
	void Update();						//更新
protected:
	enum class FARM
	{
		GROUND,
		VILLAGE,
		GATE,
		PORTAL
	};
	//定数
	static const VECTOR SCALE;			//拡大率
	static const VECTOR INIT_STAGE_POS;//初期プレイヤー座標
	//変数
	VECTOR pos;							//ポジション
	std::vector<int> model;					//モデルハンドル
};

