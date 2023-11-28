//===========================================================================
//@brief タイマークラス
//===========================================================================
#pragma once
#include"Dxlib.h"

class Timer
{
public:
	Timer();//コンストラクタ
	~Timer();//デストラクタ
	void Init(float targetTime);//初期化
	bool CountTimer();//時間の計測
	void StartTimer();//タイマー開始
	void EndTimer();//タイマー終了
	//タイマースタート判定のgetter
	const bool getIsStartTimer()const { return isStartTimer; }
	void DrawNowTimer(VECTOR playerPos);
private:
	//変数
	bool isStartTimer;//計測が始まっているか
	float nowTime;//現在の時間
	float prevTime;//計測開始時の時間
	float targetTime;//目標時間
};