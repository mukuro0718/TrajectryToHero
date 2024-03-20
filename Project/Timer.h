//===========================================================================
//@brief タイマークラス
// 何かのタイミングを決める時は、時間ではなくフレーム数で行ったほうが良いと思うので、
// 今後は実装しないほうが良い（する意味がない）
//===========================================================================
#pragma once
#include"Dxlib.h"

class Timer
{
public:
	Timer();	//コンストラクタ
	~Timer();	//デストラクタ

	const bool CountTimer();							//時間の計測
	const void Init(const float _targetTime);			//初期化
	const void StartTimer();							//タイマー開始
	const void EndTimer();								//タイマー終了
	const void DrawNowTimer(const VECTOR _playerPos);	//現在時間の描画
	//タイマースタート判定のgetter
	const bool getIsStartTimer()const { return isStartTimer; }
private:
	/*メンバ変数*/
	float nowTime;		//現在の時間
	float prevTime;		//計測開始時の時間
	float targetTime;	//目標時間
	bool  isStartTimer;	//計測が始まっているか
};