//====================================================
// @brief 爆発魔法クラス
//====================================================
#pragma once
#include<DxLib.h>
#include "Common.h"
class Explosion
{
public:
	Explosion();	//コンストラクタ
	~Explosion();	//デストラクタ

	const void Init();												//初期化
	const void Update(const bool _isDraw, const VECTOR _targetPos);	//更新
	const void Draw();												//描画

	/*getter*/
	const SphereInfo GetSphereInfo()const { return sphere; }
private:
	/*静的定数*/
	static constexpr float	MAX_RADIUS = 50.0f;	//爆発魔法最大半径
	static constexpr float	MAX_SCALE  = 0.8f;	//最大拡大率
	static constexpr float	ADD_SCALE  = 0.01f;	//拡大率増加量
	static constexpr float	ADD_ROTATE = 0.1f;	//回転率増加量
	/*内部処理関数*/
	const void SetScale(const float _scale);	//拡大率の設定
	const void SetRotate(const float _rotate);	//回転率の設定
	/*メンバ変数*/
	VECTOR		rotate;		//回転率
	VECTOR		scale;		//拡大率
	bool		isDraw;		//描画しているか
	int			modelHandle;//モデルハンドル
	SphereInfo	sphere;		//球情報
};

