//===========================================================================
//@brief 拡散するエフェクトクラス
// エフェクトの初期化と位置更新と描画を行う
//===========================================================================
#pragma once
#include<DxLib.h>
#include"EffectBase.h"

class SpreadEffect:public EffectBase
{
public:
	SpreadEffect(){}				//コンストラクタ
	SpreadEffect(int _modelHandle);	//引数ありコンストラクタ
	~SpreadEffect();				//デストラクタ

	void Init(VECTOR _pos, VECTOR _direction)override;	//更新
	void Update()override;								//更新
private:
	/*定数*/
	static constexpr int	SPHERE_RADIUS = 10;	//球の半径
	static const	 int	SPHERE_COLOR;		//球の色
	static const	 VECTOR SPHERE_SCALE;		//球のサイズ
	/*変数*/
	VECTOR initPos;	//初期描画座標
};