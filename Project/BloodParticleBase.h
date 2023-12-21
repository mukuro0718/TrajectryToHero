//===========================================================================
//@brief 血しぶきパーティクルクラス
// 攻撃の方向をもとに血しぶきの方向を決める
// その方向をもとに、ランダムな角度で進む方向を決める
// Billboardを使用して画像を描画する
// 画像はランダムで拡大縮小させる
// 位置更新の速度もランダムで増減させる
// 重力あり
//===========================================================================
#pragma once
#include<DxLib.h>
class BloodParticleBase
{
public:
	BloodParticleBase();//コンストラクタ
	~BloodParticleBase();//デストラクタ
	void Init(const VECTOR _targetDir);//初期化
	void Update();//更新
private:
	/*静的定数*/
	static constexpr float Y_DEG = 90.0f;//Y軸回転度数
	static constexpr float Z_DEG = 45.0f;//z軸回転度数
	static constexpr int RANDOM_OFFSET_RANGE = 30;//ランダムで出すオフセットの範囲
	static constexpr int RANDOM_SPEED_RANGE = 5;//ランダムで出すスピードの範囲
	static constexpr int RANDOM_SCALE_RANGE = 10;//ランダムで出すスケールの範囲
	/*内部処理関数*/
	void SetScale();						//スケールの設定
	void SetSpeed();						//速さの設定
	void SetDir(const VECTOR _targetDir);	//方向の設定
	/*メンバ変数*/
	VECTOR particleDir;	//パーティクルの方向(単位ベクトルにする)
	VECTOR moveDir;		//移動方向(単位ベクトルにする)
	VECTOR pos;			//座標	
	VECTOR scale;		//拡大率
	float  speed;		//エフェクトの飛ぶ速さ
};

