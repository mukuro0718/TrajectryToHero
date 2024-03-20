//========================================================
// @brief ステータス上昇時パーティクル
//========================================================
#pragma once
#include<DxLib.h>

class CrackerParticleBase
{
public:
	CrackerParticleBase(const int _color);	//コンストラクタ
	~CrackerParticleBase();					//デストラクタ

	const void Init(const VECTOR _initPos);	//初期化
	const void Update();					//更新
	const void Draw();						//描画
	const void OffIsDraw() { isDraw = false; }//描画フラグを下す
private:
	/*静的定数*/
	static constexpr int	SIGN_RANGE		= 1;		//符号範囲
	static constexpr int	SIZE_RANGE		= 10;		//大きさ範囲
	static constexpr int	POS_RANGE		= 5;		//座標範囲
	static constexpr int	SPEED_RANGE		= 10;		//速さの範囲
	static constexpr int	X_LIMIT			= 900;		//最大X
	static constexpr int	MAX_FRAME_COUNT = 10;		//最大フレーム
	static constexpr float	Y_LIMIT			= 250.0f;	//最大Y
	/*内部処理関数*/
	float ReturnRandomFloatValue(const bool _sign, const int _range);//ランダムでFloat型の値を返す
	/*メンバ変数*/
	VECTOR	initPos;			//初期座標
	VECTOR	vertexPos1;			//初期頂点座標１
	VECTOR	vertexPos2;			//初期頂点座標２
	VECTOR	vertexPos3;			//初期頂点座標２
	VECTOR	vertexPos2Offset;	//初期頂点２補正座標
	VECTOR	vertexPos3Offset;	//初期頂点３補正座標
	VECTOR	moveVec;			//移動ベクトル
	float	speed;				//速さ
	float	size;				//大きさ
	float	count;				//フレームカウント
	bool	isDraw;				//描画しているか
	int		color;				//色
};

