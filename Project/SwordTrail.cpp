#include "SwordTrail.h"
#include"Common.h"
/// <summary>
/// �R���X�g���N�^
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
	//�����Ȃ�
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SwordTrail::~SwordTrail()
{
	//�����Ȃ�
}
/// <summary>
/// ������
/// </summary>
void SwordTrail::Init(const int _alpha,const int _offsetX1,const int _offsetY1,const int _offsetX2,const int _offsetY2)
{
	screenWidth = WINDOW_HEIGHT;
	screenHeight = WINDOW_WIDTH;
	for (int i = 0; i < SCREEN_INDEX; ++i)
	{
		//�X�N���[���̏�����
		screen[i] = SCREEN_INIT_VALUE;
		//�w�肵���傫���̊k�̃O���t�B�b�N�����
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
/// ����������`�F�b�N
/// </summary>
void SwordTrail::ReplayInit()
{
	for (int i = 0; i < 2; ++i)
	{
		//�����X�N���[��������������ċ��Ȃ�������
		if (screen[i] != -1)
		{
			//�X�N���[�����폜
			DeleteGraph(screen[i]);
		}
		//���ɂȂ����X�N���[���ɃT�C�h��̃O���t�B�b�N������
		screen[i] = MakeScreen(screenWidth, screenHeight);
	}
	current = 0;

	notBlendDraw = 0;
}


/// <summary>
/// �폜
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
/// �X�N���[���̐ݒ�ƃX�N���[���̑|��
/// </summary>
void SwordTrail::PreRenderSwordTrail()
{
	SetDrawScreen(screen[current]);
	ClearDrawScreen();
}



void SwordTrail::PostRenderSwordTrail()
{
	//�`�惂�[�h�̎擾
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