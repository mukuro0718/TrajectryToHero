//==========================================================
//@brief 強敵UIクラス
//==========================================================
#pragma once
#include<DxLib.h>
class StrongerUI
{
public:
	StrongerUI();	//コンストラクタ
	~StrongerUI();	//デストラクタ

	const void Update(const VECTOR _enemyPos, const int _modelHandle, const int _frameNum);	//更新
	const void Draw(const float _playerLv, const float _enemyLv) const;						//描画
private:
	/*メンバ変数*/
	VECTOR	pos;		//座標
	float	size;		//サイズ
	float	angle;		//アングル
	int		imageHandle;//画像ハンドル
};

