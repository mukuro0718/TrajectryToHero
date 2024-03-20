//===========================================================================
//@brief スカイドームクラス
// スカイドームの描画を行う
// 3角形ポリゴンをブルーム効果を与えて描画する
//===========================================================================

#pragma once
#include"DxLib.h"
#include"Common.h"
#include<vector>

class BloomEffect;

using namespace std;
class Skydome
{
public:
	Skydome();	//コンストラクタ
	~Skydome();	//デストラクタ

	const void Init();										//初期化
	const void Draw();										//描画
	const void SetDrawScreenType(const float _angleX);	//描画するスクリーンの変更
	const void BloomProg();								//描画結果を描画
private:
	/*構造体・列挙体*/
	enum class ModelType
	{
		NIGNT,//夜
		CLOUD_1,//雲１
		CLOUD_2,//雲２
	};
	/*静的定数*/
	static constexpr int MODEL_NUM = 2;//モデルの数

	static const VECTOR SCALE[MODEL_NUM];		//大きさ
	static const VECTOR ADD_ROTATE[MODEL_NUM];	//追加回転率

	/*メンバ変数*/
	BloomEffect* bloom;//ブルーム

	vector<int> modelHandle;	//モデルハンドル

	VECTOR rotate[MODEL_NUM];	//回転率
	VECTOR pos;					//座標

};

