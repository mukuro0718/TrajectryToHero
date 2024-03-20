#include "BloomEffect.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BloomEffect::BloomEffect()
	:colorScreen(0)
	,highBrightScreen(0)
	,downScaleScreen(0)
	,gaussScreen(0)
	, GaussRatio(1500)
{

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
BloomEffect::~BloomEffect()
{

}
/// <summary>
/// �X�N���[���̍쐬
/// </summary>
const void BloomEffect::MakeBloomScreen()
{
	// �ʏ�̕`�挋�ʂ��������ރX�N���[���ƁA�t�B���^�[�̏������ʂ��������ރX�N���[���̍쐬
	colorScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
	highBrightScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, FALSE);
	downScaleScreen = MakeScreen(DOWN_SCALE_SCREEN_WIDTH, DOWN_SCALE_SCREEN_HEIGHT, FALSE);
	gaussScreen = MakeScreen(DOWN_SCALE_SCREEN_WIDTH, DOWN_SCALE_SCREEN_HEIGHT, FALSE);
}
/// <summary>
/// �X�V
/// </summary>
const void BloomEffect::Update()
{
	// �㉺�L�[�������ꂽ��K�E�X�t�B���^�̂ڂ����x������ύX����
	if (CheckHitKey(KEY_INPUT_UP))
	{
		GaussRatio++;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		if (GaussRatio > 0)
		{
			GaussRatio--;
		}
	}
}
/// <summary>
/// �`�悷��X�N���[����ݒ�
/// </summary>
const void BloomEffect::SetDrawScreenType()
{
	SetDrawScreen(colorScreen);
}
/// <summary>
/// �K�E�X�łڂ������摜�𓾂�
/// </summary>
/// <returns></returns>
const void BloomEffect::GetImage()
{
	// �`�挋�ʂ��獂�P�x�����݂̂𔲂��o�����摜�𓾂�
	GraphFilterBlt(colorScreen, highBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);

	// ���P�x�������W���̂P�ɏk�������摜�𓾂�
	GraphFilterBlt(highBrightScreen, downScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);

	// �W���̂P�ɏk�������摜���K�E�X�t�B���^�łڂ���
	GraphFilterBlt(downScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 16, GaussRatio);
}
const void BloomEffect::DrawNormalGraph()
{
	// �`��Ώۂ𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);
	// �ʏ�̕`�挋�ʂ�`�悷��
	DrawGraph(0, 0, colorScreen, FALSE);
}
const void BloomEffect::DrawGaussBlendGraph()
{
	// �`�惂�[�h���o�C���j�A�t�B���^�����O�ɂ���( �g�債���Ƃ��Ƀh�b�g���ڂ₯��悤�ɂ��� )
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// �`��u�����h���[�h�����Z�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	// ���P�x�������k�����Ăڂ������摜����ʂ����ς��ɂQ��`�悷��( �Q��`�悷��̂͂�薾�邭�݂���悤�ɂ��邽�� )
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gaussScreen, FALSE);
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gaussScreen, FALSE);

	// �`��u�����h���[�h���u�����h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �`�惂�[�h���A���X�g�ɖ߂�
	SetDrawMode(DX_DRAWMODE_NEAREST);
}