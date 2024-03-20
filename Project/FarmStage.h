//===========================================================================
//@brief 地面クラス/継承
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>

class FarmStage
{
public:
	FarmStage(std::vector<int> _data);	// 引数ありコンストラクタ
	~FarmStage();						// デストラクタ

	const void Init();						//初期化
	const void Draw(const bool _isFarm);		//描画
	const void Delete();						//最終処理
	const void Update(const int _playerLv);	//更新

	/*getter*/
	const VECTOR GetGatePos()const { return pos[static_cast<int>(FARM::GATE)]; }
	const int	 GetIsShowGate() const { return isShowGate; }
	const int	 GetModelHandle()const { return model[static_cast<int>(FARM::GROUND)]; }
protected:
	/*構造体・列挙体*/
	enum class FARM
	{
		GROUND,
		GATE,
		PORTAL
	};
	/*静的定数*/
	static constexpr int MODEL_NUM = 3;//モデル数

	static const VECTOR SCALE;			//拡大率
	static const VECTOR INIT_STAGE_POS;	//初期プレイヤー座標
	//変数
	std::vector<VECTOR> scale;	//大きさ
	std::vector<VECTOR> rotate;	//回転率
	std::vector<VECTOR> pos;	//ポジション
	std::vector<int>	model;	//モデルハンドル

	float portalRotate;	//ゲート回転率
	bool  isShowGate;	//ゲートが表示されているか
};

