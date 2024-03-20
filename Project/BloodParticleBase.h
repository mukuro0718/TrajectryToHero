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
	BloodParticleBase(const int _imageHandle);	//コンストラクタ
	virtual ~BloodParticleBase();				//デストラクタ

	const void Init(const VECTOR _targetDir, const VECTOR _targetPos);	//初期化
	const void Update();	//更新
	const void Draw();		//描画
private:
	/*静的定数*/
	enum class Sign
	{
		PLUS,//プラス
		MINUS,//マイナス
	};
	static constexpr float	Y_DEG				= 150.0f;//Y軸回転度数
	static constexpr float	Z_DEG				= 45.0f	;//z軸回転度数
	static constexpr float	GRAVITY				= 0.065f;//重力
	static constexpr int	RANDOM_SPEED_RANGE	= 5		;//ランダムで出すスピードの範囲
	static constexpr int	RANDOM_SCALE_RANGE	= 5		;//ランダムで出すスケールの範囲
	static constexpr int	ALPHA_REDUCED_VALUE = 5		;//アルファ減少値
	static constexpr int	RANDOM_DIR_RANGE	= 10	;//角度の範囲
	static constexpr int	SIGN_RANGE			= 1		;//符号の範囲
	static constexpr int	MAX_ALPHA			= 255	;//最大アルファ値
	/*内部処理関数*/
	const void  SetScale();	//スケールの設定
	const void  SetSpeed();	//速さの設定
	const void  SetMoveDir();//方向の設定
	const float ReturnRandomFloatValue(const int _range, const bool _useSign);//指定したランダム範囲で数字を出す
	/*メンバ変数*/
	VECTOR	moveDir;		//移動方向(単位ベクトルにする)
	VECTOR	pos;			//座標	
	float	scale;			//拡大率
	float	speed;			//パーティクルの飛ぶ速さ
	bool	isUpdateGrav;	//重力を使用するか
	int		imageHandle;	//画像ハンドル
	int		alpha;			//アルファ
	int		framecount;		//フレーム数
};