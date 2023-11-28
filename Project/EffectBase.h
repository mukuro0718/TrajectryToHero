//===========================================================================
//@brief エフェクトベースクラス
// 各エフェクトクラス必要な関数の定義を行う
//===========================================================================
#pragma once
#include<DxLib.h>

class EffectBase
{
public:
	EffectBase(){}					//コンストラクタ
	EffectBase(int _modelHandle);	//引数ありコンストラクタ
	virtual ~EffectBase();			//デストラクタ

	void Delete();	//削除
	void Draw();	//初期化

	virtual void Init(VECTOR _pos,VECTOR _direction) = 0;	//初期化
	virtual void Update() = 0;								//更新

	//座標のgetter
	const VECTOR GetPos()		const { return pos; }
	//方向のgetter
	const VECTOR GetDirection() const { return direction; }
protected:
	/*変数*/
	VECTOR pos;			//拡散するエフェクトの座標
	VECTOR direction;	//拡散する方向
	int	   modelHandle;	//拡散するエフェクトのモデル
};