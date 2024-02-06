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

	void Init();
	void Draw(const bool _isFarm);						//描画
	void Delete();						//最終処理
	void Update(const int _playerLv);						//更新
	const int GetIsShowGate() const { return isShowGate; }
	const int GetModelHandle()const { return model[static_cast<int>(FARM::GROUND)]; }
	const VECTOR GetGatePos()const { return pos[static_cast<int>(FARM::GATE)]; }
protected:
	enum class FARM
	{
		GROUND,
		VILLAGE,
		GATE,
		PORTAL
	};
	static constexpr int MODEL_NUM = 4;
	//定数
	static const VECTOR SCALE;			//拡大率
	static const VECTOR INIT_STAGE_POS;//初期プレイヤー座標
	static const VECTOR ROTATE_VILLAGE;
	//変数
	std::vector<VECTOR> scale;
	std::vector<VECTOR> rotate;
	std::vector<VECTOR> pos;							//ポジション
	std::vector<int> model;					//モデルハンドル
	float portalRotate;
	bool isShowGate;
};

