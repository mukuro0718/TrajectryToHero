//===========================================================================
//@brief FPSコントローラークラス
//===========================================================================

#include"FPSController.h"

const int FPSController::FONT_COLOR = GetColor(255,255,255);
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
FPSController::FPSController()
	:fps(0.0f)
	,startTime(0)
	,count(0)
{
}
/// <summary>
/// デストラクタ
/// </summary>
FPSController::~FPSController()
{

}
/// <summary>
/// 初期化
/// </summary>
void FPSController::Init()
{
	fps = 0.0f;
	startTime = 0;
	count = 0;
}
/// <summary>
/// FPSの平均
/// </summary>
void FPSController::Ave()
{
	//カウントが０だったらスタートタイムを初期化
	if (count == 0)
	{
		startTime = GetNowCount();
	}
	//カウントが目標FPSになったら
	if (count == static_cast<int>(SET_FPS))
	{
		//現在の時刻を取得
		int nowTime = GetNowCount();
		//FPS計算
		fps = 1000.0 / (static_cast<double>((nowTime - startTime)) / SET_FPS);
		//初期化
		startTime = 0;
		count = 0;
	}
	else
	{
		count++;
	}
}
/// <summary>
/// FPSの描画
/// </summary>
void FPSController::Draw()
{
#if _DEBUG
	//FPSの描画
	DrawFormatString(1650, 0, FONT_COLOR, "FPS:%lg", fps);
#endif // _DEBUG
}
/// <summary>
/// 目標FPSになるよう待機
/// </summary>
void FPSController::Wait()
{
	//現在の経過時間
	int elapsedTime = GetNowCount() - startTime;
	//待機時間
	int waitTime = count * 1000 / static_cast<int>(SET_FPS) - elapsedTime;
	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}
