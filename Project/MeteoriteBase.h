//===============================================
// 隕石クラス
// 隕石一つの動きを行う
//===============================================
#pragma once
#include<DxLib.h>
#include"Common.h"
class Shadow;
class MeteoriteBase
{
public:
	MeteoriteBase();//コンストラクタ
	~MeteoriteBase();//デストラクタ

	const void Init();								//初期化
	const void Update();							//更新
	const void Draw(const int _stageModelHandle);	//描画
	/*getter*/
	const SphereInfo GetSphereInfo() { return sphereInfo; }
private:
	/*静的定数*/
	static constexpr VECTOR POS_RANGE		= { 450.0f,100.0f,500.0f };	//ランダムで出す座標の範囲
	static constexpr VECTOR POS_OFFSET		= { 0.0f,200.0f,0.0f };		//座標の補正値
	static constexpr float	SHADOW_SIZE		= 20.0f;					//影の大きさ
	static constexpr float	SHADOW_HEIGHT	= 1000.0f;					//影の高さ
	static constexpr float	RADIUS			= 20.0f;					//半径
	static constexpr bool	FILL_FLAG		= true;						//球を塗りつぶすか
	static constexpr int	RADIUS_RANGE	= 7;						//半径の範囲
	static constexpr int	SPEED_RANGE		= 2;						//スピードの速さ
	static constexpr int	DIV_NUM			= 16;						//球分割数

	static const int COLOR;//色
	/*メンバ変数*/
	Shadow*		shadow;		//影

	SphereInfo	sphereInfo;	//球情報構造体
	float		speed;		//速さ
};

