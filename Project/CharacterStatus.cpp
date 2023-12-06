//===========================================================================
//@brief �X�e�[�^�X�N���X
//===========================================================================
#include"CharacterStatus.h"
#include "Common.h"
#include "SceneChanger.h"
#include "Load.h"
#include "Timer.h"
const VECTOR CharacterStatus::SET_DRAW_POS		= VGet(50.0f,50.0f,0.0f);
const int	 CharacterStatus::FONT_COLOR_WHITE	= GetColor(210, 210, 210);
const int	 CharacterStatus::FONT_COLOR_RED	= GetColor(255, 50, 50);
/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterStatus::CharacterStatus()
	:isInputPad(false)
	,isLvUP(false)
	,isShowMenu(false)
	,isFinalSelectStatus(false)
	,lvUpCount(0)
	,prevLv(1.0f)
	,backGroundImage(0)
	,nowSelectStatus(static_cast<int>(SelectStatus::ATK))
	,statusFontHandle(0)
	, inputWaitTimer(nullptr)
{
	auto& load = Load::GetInstance();
	inputWaitTimer = new Timer();
	//������
	Init();
	load.GetCharacterStatusData(&backGroundImage,&statusFontHandle);
}
/// <summary>
/// ������
/// </summary>
void CharacterStatus::Init()
{
	inputWaitTimer->Init(5);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterStatus::~CharacterStatus()
{
	Delete();
}
/// <summary>
/// �G���G�X�e�[�^�X�̏����ݒ�
/// </summary>
void CharacterStatus::InitWeakEnemyStatus()
{
	lv = 10.0f;			//���x���̃Z�b�g
	hp = 50.0f;		//�̗͂̃Z�b�g
	atk = 10.0f;			//�U���͂̃Z�b�g
	def = 50.0f;			//�h��͂̃Z�b�g
	agi = 1.0f;			//�f�����̃Z�b�g
	expToGive = 5.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp = 0.0f;			//�o���l�̃Z�b�g
	needExp = 0.0f;
	maxHp = hp;
}
/// <summary>
/// ���{�X�X�e�[�^�X�̏����ݒ�
/// </summary>
void CharacterStatus::InitStrongEnemyStatus()
{
	lv = 10.0f;			//���x���̃Z�b�g
	hp = 100.0f;		//�̗͂̃Z�b�g
	atk = 20.0f;			//�U���͂̃Z�b�g
	def = 60.0f;			//�h��͂̃Z�b�g
	agi = 2.0f;			//�f�����̃Z�b�g
	expToGive = 15.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp = 0;			//�o���l�̃Z�b�g
	needExp = 0.0f;
	maxHp = hp;
}
/// <summary>
/// �{�X�X�e�[�^�X�̏����ݒ�
/// </summary>
void CharacterStatus::InitBossEnemyStatus()
{
	lv			= 10.0f;	//���x���̃Z�b�g
	hp			= 300.0f;	//�̗͂̃Z�b�g
	atk			= 30.0f;	//�U���͂̃Z�b�g
	def			= 70.0f;	//�h��͂̃Z�b�g
	agi			=2.0f;		//�f�����̃Z�b�g
	expToGive = 10.0f;		//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp			= 0.0f;		//�o���l�̃Z�b�g
	needExp = 0.0f;
	maxHp = hp;
}

/// <summary>
/// �v���C���[�X�e�[�^�X�̏����ݒ�
/// </summary>
void CharacterStatus::InitPlayerStatus()
{
	lv			 = 1.0f;	//���x���̃Z�b�g
	hp			 = 30.0f;	//�̗͂̃Z�b�g
	atk		 = 3.0f;	//�U���͂̃Z�b�g
	def		 = 1.0f;	//�h��͂̃Z�b�g
	agi		 = 1.5f;	//�f�����̃Z�b�g
	expToGive = 0.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp		 = 0.0f;	//�o���l�̃Z�b�g
	needExp = 10.0f;
	maxHp = hp;
}

/// <summary>
/// HP�v�Z
/// </summary>
float CharacterStatus::CalcHP(const float _atk)
{
	hp -= atk * def * 0.05f;
	if (hp <= 0)
	{
		return expToGive;
	}
	return 0.0f;
}
/// <summary>
/// �^����o���l�̏�����
/// </summary>
void CharacterStatus::InitExpToGive()
{
	expToGive = 0.0f;
}
/// <summary>
/// HP�v�Z
/// </summary>
void CharacterStatus::CalcExp(const float _expToGive)
{
	//�o���l�𑫂�
	exp += _expToGive;
	//�����o���l�ʂ����x���A�b�v�ɕK�v�Ȍo���l�ʂ𒴂��Ă�����
	if (exp >= needExp)
	{
		//���x���A�b�v
		++lv;
		//�o���l�ʂ̏�����
		exp -= needExp;
		//���ɕK�v�Ȍo���l�ʂ�ݒ�
		needExp = lv * 10;
	}

}
/// <summary>
/// �摜�n���h���A�N���X�C���X�^���X�̍폜
/// </summary>
void CharacterStatus::Delete()
{
	// ���f���̃A�����[�h
	DeleteGraph(backGroundImage);
	//�C���X�^���X�̍폜
	if (inputWaitTimer)
	{
		delete(inputWaitTimer);
		inputWaitTimer = nullptr;
	}
}

/// <summary>
/// �X�V
/// </summary>
void CharacterStatus::Update()
{
	lvUpCount = static_cast<int>(lv) - static_cast<int>(prevLv);
	//���x���A�b�v�����Ă�����
	if (lvUpCount > 0)
	{
		isShowMenu = true;
		//�I���X�e�[�^�X�̕ύX
		ChangeSelectStatus();
		//�I�����Ă���X�e�[�^�X�̏㏸
		UpSelectStatus();
	}
	else
	{
		nowSelectStatus = static_cast<int>(SelectStatus::ATK);
		isShowMenu = false;
	}
}
/// <summary>
/// �`��
/// </summary>
void CharacterStatus::Draw()
{
	// ���j���[���J���Ă���Ƃ�
	if (isShowMenu)
	{
		DrawExtendGraph(BACKGROUND_POS.x, BACKGROUND_POS.y, BACKGROUND_POS.x + BACKGROUND_WIDTH, BACKGROUND_POS.y + BACKGROUND_HEIGHT, backGroundImage, TRUE);
		DrawStringToHandle(STATUS_UP_TEXT_POS.x, STATUS_UP_TEXT_POS.y, "STATUS UP!", FONT_COLOR_WHITE, statusFontHandle);
		//�I�����ꂢ�Ȃ��A�C�R���͏����Â�����
		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::ATK));	//�U����
		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::DEF));	//�h���
		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::AGI));	//�f����
	}
}
/// <summary>
/// �I�����Ă���X�e�[�^�X�̏㏸
/// </summary>
void CharacterStatus::UpSelectStatus()
{
	//�ŏI���肳��Ă�����
	if (isFinalSelectStatus && lvUpCount != 0)
	{
		//�I�����Ă���X�e�[�^�X�̏㏸
		switch (nowSelectStatus)
		{
		case static_cast<int>(SelectStatus::ATK):
			atk += LV_UP_ADD_VALUE;
			break;
		case static_cast<int>(SelectStatus::DEF):
			def += LV_UP_ADD_VALUE;
			break;
		case static_cast<int>(SelectStatus::AGI):
			agi += LV_UP_ADD_VALUE;
			break;
		}
		//�t���O��܂�
		isFinalSelectStatus = false;
		prevLv++;
	}
}
/// <summary>
/// �I�����ꂽ/����Ă��Ȃ��𓧖��x��ς��ĕ\��
/// </summary>
/// <param name="nowSelectStatus">���ݑI�𒆂̃X�e�[�^�X</param>
/// <param name="statusType">�X�e�[�^�X�̎��</param>
/// <param name="imgHandle"></param>
void CharacterStatus::ChangeBlendRateDrawText(const int currentSelectStatus, const int statusType)
{
	const TCHAR* drawText = NULL;
	switch (statusType)
	{
	case static_cast<int>(SelectStatus::ATK):
		drawText = "ATK";
		break;
	case static_cast<int>(SelectStatus::DEF):
		drawText = "DEF";
		break;
	case static_cast<int>(SelectStatus::AGI):
		drawText = "AGI";
		break;
	}
	// �J�[�\���ԍ����������Ƃ��͑I�����Ă���
	// �I������Ă���Ƃ��͕��ʂɕ`�悷��
	if (nowSelectStatus == statusType)
	{
		//���x���A�b�v���Ă�����button�摜��\������
		DrawStringToHandle(STATUS_TEXT_POS[statusType].x, STATUS_TEXT_POS[statusType].y, drawText, FONT_COLOR_RED, statusFontHandle);
	}
	//�I������Ă��Ȃ��Ƃ��͏����Â��`�悷��
	else
	{
		// ��I�����̉摜�̕`��i�I������Ă��Ȃ��摜�𔖂�����j
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawStringToHandle(STATUS_TEXT_POS[statusType].x, STATUS_TEXT_POS[statusType].y, drawText, FONT_COLOR_RED, statusFontHandle);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

/// <summary>
/// �A�C�R���̑I���i�J�[�\���̔ԍ���؂�ւ���j
/// </summary>
void CharacterStatus::ChangeSelectStatus()
{
	// �L�[�̓��͏�Ԃ��Ƃ�
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//���
	if (!isInputPad)
	{
		if (input & PAD_INPUT_UP)
		{
			switch (nowSelectStatus)
			{
			case static_cast<int>(SelectStatus::ATK):
				nowSelectStatus = static_cast<int>(SelectStatus::ATK);
				break;
			case static_cast<int>(SelectStatus::DEF):
				nowSelectStatus = static_cast<int>(SelectStatus::ATK);
				break;
			case static_cast<int>(SelectStatus::AGI):
				nowSelectStatus = static_cast<int>(SelectStatus::DEF);
				break;
			}
			isInputPad = true;
		}
		// ����
		if (input & PAD_INPUT_DOWN)
		{
			switch (nowSelectStatus)
			{
			case static_cast<int>(SelectStatus::ATK):
				nowSelectStatus = static_cast<int>(SelectStatus::DEF);
				break;
			case static_cast<int>(SelectStatus::DEF):
				nowSelectStatus = static_cast<int>(SelectStatus::AGI);
				break;
			case static_cast<int>(SelectStatus::AGI):
				nowSelectStatus = static_cast<int>(SelectStatus::AGI);
				break;
			}
			isInputPad = true;
		}
	}
	else
	{
		inputWaitTimer->StartTimer();
	}
	if (inputWaitTimer->CountTimer())
	{
		isInputPad = false;
		inputWaitTimer->EndTimer();
	}
	// �ŏI�I��
	if (input & PAD_INPUT_2)
	{
		isFinalSelectStatus = true;
		isInputPad = true;
	}
}
/// <summary>
/// ���̕\��
/// </summary>
void CharacterStatus::ShowInfo()
{
	printfDx("STATUS\n");
	printfDx("LV:%f\n", lv);
	printfDx("HP:%f\n", hp);
	printfDx("ATK:%f\n", atk);
	printfDx("DEF:%f\n", def);
	printfDx("AGI:%f\n", agi);
	printfDx("EXP:%f\n", exp);
	printfDx("needEXP:%f\n", needExp);
	printfDx("maxHP:%f\n", maxHp);
}