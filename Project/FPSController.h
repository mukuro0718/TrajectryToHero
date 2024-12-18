//===========================================================================
//@brief FPSコントローラークラス
// FPSの設定、計算と描画を行う
// https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q10175479905より引用
//===========================================================================
#pragma once
#include"DxLib.h"
class FPSController
{
public:
	FPSController();
	~FPSController();
	const void Init();	//初期化
	const void Ave();	//FPSの平均を算出
	const void Draw();	//FPSを表示
	const void Wait();	//目標FPSになるよう待機
private:
	/*静的定数*/
	static constexpr double SET_FPS = 60.0;//目標FPS
	
	static const int FONT_COLOR;//文字の色

	/*メンバ変数*/
	double	fps;		//fps
	int		startTime;	//計測開始時間
	int		count;		//処理回数
};