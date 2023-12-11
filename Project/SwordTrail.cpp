#include "SwordTrail.h"
#include"Common.h"
/// <summary>
/// コンストラクタ
/// </summary>
SwordTrail::SwordTrail()
	: screen{0,0}
	, current(0)
	, alpha(0)
	, screenWidth(0)
	, screenHeight(0)
	, offsetX1(0)
	, offsetY1(0)
	, offsetX2(0)
	, offsetY2(0)
	,notBlendDraw(0)
{
	//処理なし
}
/// <summary>
/// デストラクタ
/// </summary>
SwordTrail::~SwordTrail()
{
	//処理なし
}
/// <summary>
/// 初期化
/// </summary>
void SwordTrail::Init(const int _alpha,const int _offsetX1,const int _offsetY1,const int _offsetX2,const int _offsetY2)
{
	screenWidth = WINDOW_HEIGHT;
	screenHeight = WINDOW_WIDTH;
	for (int i = 0; i < SCREEN_INDEX; ++i)
	{
		//スクリーンの初期化
		screen[i] = SCREEN_INIT_VALUE;
		//指定した大きさの殻のグラフィックを作る
		screen[i] = MakeScreen(screenWidth, screenHeight);
	}
	current = 0;
	alpha = _alpha;
	offsetX1 = _offsetX1;
	offsetX2 = _offsetX2;
	offsetY1 = _offsetY1;
	offsetY2 = _offsetY2;

	notBlendDraw = 0;
}


/// <summary>
/// 初期化もれチェック
/// </summary>
void SwordTrail::ReplayInit()
{
	for (int i = 0; i < 2; ++i)
	{
		//もしスクリーンが初期化されて居なかったら
		if (screen[i] != -1)
		{
			//スクリーンを削除
			DeleteGraph(screen[i]);
		}
		//唐になったスクリーンにサイド空のグラフィックを入れる
		screen[i] = MakeScreen(screenWidth, screenHeight);
	}
	current = 0;

	notBlendDraw = 0;
}


/// <summary>
/// 削除
/// </summary>
void SwordTrail::Delete()
{
	for (int i = 0; i < 2; ++i)
	{
		if (screen[i] != -1)
		{
			DeleteGraph(screen[i]);
		}
	}
}


/// <summary>
/// スクリーンの設定とスクリーンの掃除
/// </summary>
void SwordTrail::PreRenderSwordTrail()
{
	SetDrawScreen(screen[current]);
	ClearDrawScreen();
}



void SwordTrail::PostRenderSwordTrail()
{
	//描画モードの取得
	int drawMode = GetDrawMode();
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	int blendMode, param;
	GetDrawBlendMode(&blendMode, &param);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	if (notBlendDraw++ > 2)
	{
		DrawExtendGraph(offsetX1, offsetY1, screenWidth + offsetX2, screenHeight + offsetY2, screen[1 - current], false);
	}
	SetDrawBlendMode(blendMode, param);
	SetDrawMode(drawMode);

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, screen[current], false);
	current = 1 - current;
}