//===========================================================================
//@brief スカイドームクラス
// スカイドームの描画を行う
// 3角形ポリゴンをブルーム効果を与えて描画する
//===========================================================================

#pragma once
#include"DxLib.h"
#include"Common.h"

class Star;
class BloomEffect;
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
	static constexpr int POLYGON_NUM = 500;
	static const VERTEX3D ORIGIN_VERTEX;
	static const COLOR_U8 STAR_COLOR;			//軌跡の色
	/*メンバ変数*/
	VECTOR pos;
	int modelHandle;
	int vertexIndex;
	VERTEX3D vertexPos[POLYGON_NUM * 3];//頂点座標
	Star* star[POLYGON_NUM];
	BloomEffect* bloom;
};

