#include "LoadScene.h"
#include "Common.h"

const int LoadScene::FONT_COLOR = GetColor(255,255,255);

/// <summary>
/// コンストラクタ
/// </summary>
LoadScene::LoadScene()
	:alpha(MIN_ALPHA)
	, isIncTheValue(false)
	, isIncWaitFrameCount(0)
	, updateWaitFrameCount(0)
{
	
	Init();
}
/// <summary>
/// デストラクタ
/// </summary>
LoadScene::~LoadScene()
{
	Final();
}
/// <summary>
/// 初期化
/// </summary>
const void LoadScene::Init()
{
	SetFontSize(FONT_SIZE);
}
/// <summary>
/// 後処理
/// </summary>
const void LoadScene::Final()
{
}
/// <summary>
/// 更新
/// </summary>
const void LoadScene::Update()
{
	updateWaitFrameCount++;
	if (updateWaitFrameCount >= MAX_UPDATE_WAIT_FRAME_COUNT)
	{
		//増減の変更
		if (isIncTheValue)
		{
			alpha += ADD_ALPHA;
			if (alpha >= MAX_ALPHA)
			{
				isIncWaitFrameCount++;
				if (isIncWaitFrameCount >= MAX_IS_INC_WAIT_FRAME_COUNT)
				{
					isIncWaitFrameCount = 0;
					isIncTheValue = false;
				}
				alpha = MAX_ALPHA;
			}
		}
		else
		{
			alpha -= ADD_ALPHA;
			if (alpha <= MIN_ALPHA)
			{
				isIncWaitFrameCount++;
				if (isIncWaitFrameCount >= MAX_IS_INC_WAIT_FRAME_COUNT)
				{
					isIncWaitFrameCount = 0;
					isIncTheValue = true;
				}
				alpha = MIN_ALPHA;
			}
		}
		updateWaitFrameCount = 0;
	}
}
/// <summary>
/// 描画
/// </summary>
const void LoadScene::Draw()
{
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawString(X,Y,"Now Loading", FONT_COLOR);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}