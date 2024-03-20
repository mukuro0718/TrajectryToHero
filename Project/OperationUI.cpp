#include "OperationUI.h"
#include"Load.h"
const int OperationUI::FONT_COLOR = GetColor(200, 200, 200);

/// <summary>
/// �R���X�g���N�^
/// </summary>
OperationUI::OperationUI()
	: alpha(MAX_ALPHA)
	, moveUI(0)
	, menuUI(0)
	, attackUI(0)
	, cameraUI(0)
	, strongUI(0)
{
	auto& load = Load::GetInstance();
	load.GetStrongerUIData(&strongUI);
	load.GetOpeUIData(&moveUI, &menuUI, &attackUI, &cameraUI);
	textFont = CreateFontToHandle("Data/Font/Honoka_Shin_Mincho_L.otf", 24, 32, DX_FONTTYPE_NORMAL);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
OperationUI::~OperationUI()
{
	//�����Ȃ�
}
/// <summary>
/// �X�V
/// </summary>
const void OperationUI::Update(const bool _isMove)
{
	if (!_isMove)
	{
		alpha += ADD_ALPHA_VALUE;
		if (alpha > MAX_ALPHA)
		{
			alpha = MAX_ALPHA;
		}
	}
	else
	{
		alpha = MIN_ALPHA;
	}
}
/// <summary>
/// �`��
/// </summary>
const void OperationUI::Draw(const VECTOR _bonfirePos, const VECTOR _playerPos)
{
	VECTOR bonfirePos = _bonfirePos;
	bonfirePos.y = 0;
	VECTOR fireToPlayer = VSub(_bonfirePos, _playerPos);
	float vecSize = VSize(fireToPlayer);

	if (vecSize < 30.0f)
	{
		DrawExtendGraph(BONFIRE_MENU_UI_DRAW_RECT.LX, BONFIRE_MENU_UI_DRAW_RECT.LY, BONFIRE_MENU_UI_DRAW_RECT.RX, BONFIRE_MENU_UI_DRAW_RECT.RY, menuUI, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//�����p�̔w�i�摜�̕`��
	DrawBox(BACKGROUND_POS_FOR_DESCRIPTION.LX, BACKGROUND_POS_FOR_DESCRIPTION.LY, BACKGROUND_POS_FOR_DESCRIPTION.RX, BACKGROUND_POS_FOR_DESCRIPTION.RY, GetColor(0, 0, 0), TRUE);
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y, "�G��|���ƁA�o���l���擾�ł��܂��B\n���x�����オ��ƁA�X�e�[�^�X�|�C���g��\n�t�^����܂��B", FONT_COLOR, textFont);
	//�����p�̔w�i�摜�̕`��
	DrawExtendGraph(1390, 150, 1500, 230, strongUI, TRUE);
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x + 70, TEXT_POS_FOR_DESCRIPTION.y + 100, "���̃}�[�N�����Ă���G��,\n���Ȃ��������x������̓G�ł��B\n�X�e�[�^�X���������Ē��݂܂��傤�B", FONT_COLOR, textFont);
	//�����p�̔w�i�摜�̕`��
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y + 200, "�����΂ŋx�ނƁA�̗͂��񕜂��邱�Ƃ�\n�ł��܂��B\n�܂����x���A�b�v���j���[��I������ƁA\n�X�e�[�^�X�|�C���g������ăX�e�[�^�X\n�������ł��܂��B", FONT_COLOR, textFont);
	//�����p�̔w�i�摜�̕`��
	DrawStringToHandle(TEXT_POS_FOR_DESCRIPTION.x, TEXT_POS_FOR_DESCRIPTION.y + 350, "���x�������ȏ�オ��ƁA�Q�[�g���o��\n���܂��B\n�Q�[�g��������ƃ{�X�킪�n�܂�̂ŁA\n�X�e�[�^�X���������Ē��݂܂��傤�B", FONT_COLOR, textFont);
	DrawExtendGraph(MOVE_UI_DRAW_RECT.LX, MOVE_UI_DRAW_RECT.LY, MOVE_UI_DRAW_RECT.RX, MOVE_UI_DRAW_RECT.RY, moveUI, TRUE);
	DrawExtendGraph(ATTACK_UI_DRAW_RECT.LX, ATTACK_UI_DRAW_RECT.LY, ATTACK_UI_DRAW_RECT.RX, ATTACK_UI_DRAW_RECT.RY, attackUI, TRUE);
	DrawExtendGraph(CAMERA_UI_DRAW_RECT.LX, CAMERA_UI_DRAW_RECT.LY, CAMERA_UI_DRAW_RECT.RX, CAMERA_UI_DRAW_RECT.RY, cameraUI, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, MAX_ALPHA);
}