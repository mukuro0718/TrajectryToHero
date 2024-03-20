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

	const void Draw();						//描画
	const void Delete();						//最終処理
	const void Update();						//更新
protected:
	/*構造体・列挙体*/
	enum class FARM
	{
		GROUND,
		VILLAGE,
		GATE,
		PORTAL
	};
	/*静的定数*/
	static const VECTOR SCALE;			//拡大率
	static const VECTOR INIT_STAGE_POS;	//初期プレイヤー座標
	/*変数*/
	std::vector<int> model;	//モデルハンドル
	VECTOR pos;				//ポジション
};

