//===========================================================================
//@brief 拡散するエフェクトクラス
// 血しぶきを出す
//===========================================================================
#pragma once
#include<DxLib.h>

class BloodParticle
{
public:
	BloodParticle();				//コンストラクタ
	~BloodParticle();				//デストラクタ

private:
	/*定数*/
	static constexpr int	SPHERE_RADIUS = 10;	//球の半径
	static const	 int	SPHERE_COLOR;		//球の色
	static const	 VECTOR SPHERE_SCALE;		//球のサイズ
	/*変数*/
	VECTOR initPos;	//初期描画座標
};