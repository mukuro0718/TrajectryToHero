#pragma once
#include<DxLib.h>
#include<vector>
class FireParticle
{
public:
	FireParticle(const VECTOR _centerPos, const int _particleData);//コンストラクタ
	~FireParticle();//デストラクタ

	const void Init();	//初期化
	const void Update();//更新
	const void Draw();	//描画

private:
	/*静的定数*/
	static constexpr float	SIZE_REDUCED_VALUE	= 0.4f;	//サイズ減少値
	static constexpr float	CX					= 0.5;	//CX
	static constexpr float	CY					= 0.5f;	//CY
	static constexpr float	ANGLE				= 0.0f;	//アングル
	static constexpr int	SIGN_RANGE			= 1;	//符号範囲
	static constexpr int	X_POS_RANGE			= 5;	//X範囲
	static constexpr int	Z_POS_RANGE			= 5;	//Z範囲
	static constexpr int	SPEED_RANGE			= 2;	//速さの範囲
	static constexpr int	ALPHA_RANGE			= 255;	//アルファ範囲
	static constexpr int	ALPHA_MAX_VALUE		= 255;	//アルファ最大値
	static constexpr int	ALPHA_REDUCED_VALUE = 10;	//アルファ減少値

	/*内部処理関数*/
	const float ReturnRandomFloat(const bool _useSign, const int _range);//Float型のランダムを返す
	/*メンバ変数*/
	VECTOR	centerPos;		//中心座標
	VECTOR	pos;			//座標
	float	size;			//サイズ
	float	speed;			//速さ
	bool	isDraw;			//描画するか
	int		alpha;			//アルファ
    int		particleData;	//パーティクル画像
};

