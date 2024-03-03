//================================================
// @brief 星クラス
// 3つの頂点を保持し、三角形のポリゴンを描画する
//================================================
#pragma once
#include<DxLib.h>
#include<vector>
class Star
{
public:
	Star();//コンストラクタ
	~Star();//デストラクタ
	const VECTOR& GetVertex(const int _index)const { return vertex[_index]; }
private:
	/*静的定数*/
	static constexpr int VERTEX_NUM = 3;//頂点数
	static constexpr int POS_RANGE = 800;
	static constexpr int SIGN_RANGE = 1;
	static constexpr int SCALE = 10;
	/*メンバ変数*/
	VECTOR vertex[VERTEX_NUM];
	const VECTOR GetRandomFirstPos();
	const VECTOR GetRandomOtherPos();
};

