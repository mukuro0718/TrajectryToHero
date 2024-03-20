//===========================================================================
//@brief タイマークラス
//===========================================================================
#include"Timer.h"

/// <summary>
/// 引数ありコンストラクタ
/// </summary>
/// <param name="targetTime">目標時間</param>
Timer::Timer()
	: nowTime(0.0f)
	, prevTime(0.0f)
	, targetTime(0.0f)
	, isStartTimer(0)
{
	//SetFontSize(64);
}
/// <summary>
/// デストラクタ
/// </summary>
Timer::~Timer()
{
	//処理なし
}
/// <summary>
/// 初期化
/// </summary>
/// <param name="targetTime">目標時間</param>
const void Timer::Init(float targetTime)
{
	isStartTimer = false;
	this->targetTime = targetTime * 100.0f;
	nowTime = prevTime = 0.0f;
}
/// <summary>
/// タイマー開始
/// </summary>
const void Timer::StartTimer()
{
	if (!isStartTimer)
	{
		nowTime = prevTime = static_cast<float>(GetNowCount());
		isStartTimer = true;
	}
}
/// <summary>
/// タイマー終了
/// </summary>
const void Timer::EndTimer()
{
	if (isStartTimer)
	{
		nowTime = prevTime = 0.0f;
		isStartTimer = false;
	}
}
/// <summary>
/// 時間の計測
/// </summary>
/// <returns>true/false</returns>
const bool Timer::CountTimer()
{
	if (isStartTimer)
	{
		nowTime = static_cast<float>(GetNowCount());
		//目標時間を越していたらtrueを返す
		if (nowTime - prevTime >= targetTime)
		{
			nowTime = prevTime = static_cast<float>(GetNowCount());
			return true;
		}
	}
	return false;
}
/// <summary>
/// タイマーの表示
/// </summary>
/// <param name="playerPos">プレイヤーの０番目のフレームの座標</param>
const void Timer::DrawNowTimer(VECTOR playerPos)
{
	//clsDx();
	//プレイヤーの０番目のフレームのワールド座標を基にスクリーン座標を出す
	//VECTOR screenPos = ConvWorldPosToScreenPos(playerPos);
	//DrawFormatString(static_cast<int>(screenPos.x), static_cast<int> ( screenPos.y), GetColor(255, 255, 255), "Time:%f", prevTime + targetTime - nowTime);
}