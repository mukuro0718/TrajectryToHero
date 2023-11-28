//===========================================================================
//@brief エフェクト管理クラス
// エフェクトの管理と関数の実行を行う
//===========================================================================
#pragma once
#include<DxLib.h>

class EffectBase;

class EffectManager
{
public:
	EffectManager();//コンストラクタ
	~EffectManager();//デストラクタ
	void Create();//生成
	void Init();//初期化
	void Final();//削除
	void SpreadEffectManager(VECTOR _pos, bool isInvicible);//拡散するエフェクトの管理（描画、更新）
private:
	//定数
	enum class Direction
	{
		PLUS_X,
		PLUS_XY,
		PLUS_X_MINUS_Y,
		PLUS_XZ,
		PLUS_X_MINUS_Z,
		PLUS_XYZ,
		PLUS_XY_MINUS_Z,
		PLUS_XZ_MINUS_Y,
		PLUS_X_MINUS_YZ,

		MINUS_X,
		MINUS_X_PLUS_Y,
		MINUS_XY,
		MINUS_X_PLUS_Z,
		MINUS_XZ,
		MINUS_X_PLUS_YZ,
		MINUS_XZ_PLUS_Y,
		MINUS_XY_PLUS_Z,
		MINUS_XYZ,

		PLUS_Y,
		PLUS_YZ,
		PLUS_Y_MINUS_Z,

		MINUS_Y,
		MINUS_Y_PLUS_Z,
		MINUS_YZ,

		PLUS_Z,
		MINUS_Z,
	};
	static constexpr int DIRECTION_NUM = 26;//拡散するエフェクトの方向数
	static const VECTOR DIRECTION[DIRECTION_NUM];//ベクトルの方向
	static constexpr int SPREAD_CIRCLE_RADIUS = 10;
	static const int SPREAD_CIRCLE_COLOR;
	//クラス
	EffectBase* spreadEffect[DIRECTION_NUM];
	/*変数*/
	bool isShowSpreadEffect;//拡散するエフェクトを表示しているか
	VECTOR spreadFirstPos;
};