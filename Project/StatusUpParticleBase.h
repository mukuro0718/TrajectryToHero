//=======================================================
// @brief　レベルアップ・HP回復時パーティクル
//=======================================================
#pragma once
#include<DxLib.h>
#include"Common.h"
class StatusUpParticleBase
{
public:
	StatusUpParticleBase(const int _imageHandle);	//コンストラクタ
	~StatusUpParticleBase();						//デストラクタ

	const void Init();							//初期化
	const void Update(const VECTOR _targetPos);	//更新
	const void Draw();							//描画
private:
	/*静的定数*/
	static constexpr int SIZE_RANGE		 = 5;	//サイズ範囲
	static constexpr int SIGN_RANGE		 = 1;	//符号範囲
	static constexpr int POS_RANGE		 = 10;	//座標範囲
	static constexpr int SPEED_RANGE	 = 5;	//スピード範囲
	static constexpr int ALPHA_RANGE	 = 10;	//アルファ範囲
	static constexpr int MAX_ALPHA_VALUE = 200;	//最大アルファ
	static constexpr int MIN_ALPHA_VALUE = 0;	//最小アルファ
	/*内部処理関数*/
	const float ReturnRandomFloatValue(const bool _sign, const int _range);//ランダムでFloat型の値を返す
	/*メンバ変数*/
	VECTOR	targetPos;		//目標座標
	VECTOR	offsetPos;		//補正座標
	float	size;			//サイズ
	float	speed;			//速さ
	int		addAlphaValue;	//追加アルファ
	int		alpha;			//アルファ
	int		imageHandle;	//画像ハンドル
	int		frameCount;		//フレームカウント
};

