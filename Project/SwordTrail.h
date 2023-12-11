//===========================================================================
//@brief 画面ブラークラス
// 参考URL https://haina.hatenablog.com/entry/2016/05/17/230902
// 最初の座標がセットされたらタイマーをスタートさせる
// タイマーが目標時間に達したらその時の座標をまた記憶する
// 
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>
class SwordTrail
{
public:
	SwordTrail();//コンストラクタ
	~SwordTrail();//デストラクタ

	void Init();
	void Delete();

private:
	std::vector < VERTEX3D > vertexTipPos;//先端頂点座標
	std::vector < VERTEX3D > vertexEndPos;//末端頂点座標

	int vertexInfoCurrentHeldNum;//現在保持している頂点情報
};
