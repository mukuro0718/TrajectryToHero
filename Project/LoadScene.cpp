#include "LoadScene.h"
#include "Common.h"

const int LoadScene::FONT_COLOR = GetColor(255,255,255);

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N�^
/// </summary>
LoadScene::~LoadScene()
{
	Final();
}
/// <summary>
/// ������
/// </summary>
const void LoadScene::Init()
{
	SetFontSize(FONT_SIZE);
}
/// <summary>
/// �㏈��
/// </summary>
const void LoadScene::Final()
{
}
/// <summary>
/// �X�V
/// </summary>
const void LoadScene::Update()
{
	updateWaitFrameCount++;
	if (updateWaitFrameCount >= MAX_UPDATE_WAIT_FRAME_COUNT)
	{
		//�����̕ύX
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
/// �`��
/// </summary>
const void LoadScene::Draw()
{
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawString(X,Y,"Now Loading", FONT_COLOR);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}