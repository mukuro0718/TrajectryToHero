//===========================================================================
//@brief スカイドームクラス
// スカイドームの描画を行う
//===========================================================================

#pragma once
#include"DxLib.h"
#include"Common.h"

class Skydome
{
public:
	Skydome();//コンストラクタ
	~Skydome();//デストラクタ

	void Init();//初期化
	void Draw();//描画
private:
	/*静的定数*/
	static const VECTOR SCALE;
	/*メンバ変数*/
	VECTOR pos;
	int modelHandle;
};

