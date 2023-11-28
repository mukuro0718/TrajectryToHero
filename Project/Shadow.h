//========================================
// 影クラス
// プレイヤーとエネミーに対して丸影の描画を行う
//========================================

#pragma once
#include"DxLib.h"
#include<math.h>
class Shadow
{
public:
	Shadow();	//コンストラクタ
	~Shadow();	//デストラクタ
	void Final();//最終処理
	void Draw(const int _stageModelHandle, const VECTOR _targetPos, const float _shadowHeight, const float _shadowSize);//影を描画
private:
	int shadowHandle;//影画像ハンドル
};

