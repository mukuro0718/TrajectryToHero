////===========================================================================
////@brief �X�e�[�^�X�Ǘ��N���X
//// �X�e�[�^�X�v�Z�A�X�e�[�^�X�摜�̕`��
////===========================================================================
//#include "StatusManager.h"
//#include "Common.h"
//#include "ScenesCommon.h"
//#include "SceneChanger.h"
//#include "Load.h"
//#include "Timer.h"
//
//constexpr VECTOR StatusManager::SET_DRAW_POS = VGet(50.0f,50.0f,0.0f);
//const int StatusManager::FONT_COLOR_WHITE = GetColor(210, 210, 210);
//const int StatusManager::FONT_COLOR_RED = GetColor(255, 50, 50);
///// <summary>
///// �R���X�g���N�^
///// </summary>
//StatusManager::StatusManager()
//{
//	//�N���X�C���X�^���X�̍쐬
//	CreateInstance();
//	auto& load = Load::GetInstance();
//	//������
//	Init();
//	load.GetStatusManagerData(&backGroundImage);
//	
//}
//
///// <summary>
///// �f�X�g���N�^
///// </summary>
//StatusManager::~StatusManager()
//{
//	Delete();
//}
///// <summary>
///// ������
///// </summary>
//void StatusManager::Init()
//{
//	inputWaitTimer->Init(5);
//	isInputPad			= false;
//	isLvUP				= false;
//	isShowMenu			= false;
//	isFinalSelectStatus = false;
//	prevLv				= 1.0f;
//	lvUpCount			= 0;
//	backGroundImage		= 0;
//	nowSelectStatus		= static_cast<int>(SelectStatus::ATK);
//	statusFontHandle	= CreateFontToHandle("Data/Img/Font/HelpMe.ttf", FONT_SIZE, FONT_THICK, DX_FONTTYPE_NORMAL);
//}
///// <summary>
///// �N���X�C���X�^���X�̐���
///// </summary>
//void StatusManager::CreateInstance()
//{
//	inputWaitTimer = NULL;
//	inputWaitTimer = new Timer();
//}
///// <summary>
///// �摜�n���h���A�N���X�C���X�^���X�̍폜
///// </summary>
//void StatusManager::Delete()
//{
//	// ���f���̃A�����[�h
//	DeleteGraph(backGroundImage);
//	//�C���X�^���X�̍폜
//	if (inputWaitTimer)
//	{
//		delete(inputWaitTimer);
//		inputWaitTimer = NULL;
//	}
//}
///// <summary>
///// �X�V
///// </summary>
//void StatusManager::Update(CharacterStatus* status)
//{
//	lvUpCount = static_cast<int>(status->LV) - static_cast<int>(prevLv);
//	//���x���A�b�v�����Ă�����
//	if (lvUpCount > 0)
//	{
//		isShowMenu = true;
//		//�I���X�e�[�^�X�̕ύX
//		ChangeSelectStatus();
//		//�I�����Ă���X�e�[�^�X�̏㏸
//		UpSelectStatus(status);
//	}
//	else
//	{
//		nowSelectStatus = static_cast<int>(SelectStatus::ATK);
//		isShowMenu = false;
//	}
//}
///// <summary>
///// �`��
///// </summary>
//void StatusManager::Draw()
//{
//	// ���j���[���J���Ă���Ƃ�
//	if (isShowMenu)
//	{
//		DrawExtendGraph(BACKGROUND_POS.x, BACKGROUND_POS.y, BACKGROUND_POS.x + BACKGROUND_WIDTH, BACKGROUND_POS.y + BACKGROUND_HEIGHT, backGroundImage,TRUE);
//		DrawStringToHandle(STATUS_UP_TEXT_POS.x, STATUS_UP_TEXT_POS.y, "STATUS UP!", FONT_COLOR_WHITE, statusFontHandle);
//		//�I�����ꂢ�Ȃ��A�C�R���͏����Â�����
//		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::ATK));	//�U����
//		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::DEF));	//�h���
//		ChangeBlendRateDrawText(nowSelectStatus, static_cast<int>(SelectStatus::AGI));	//�f����
//	}
//}
///// <summary>
///// �I�����Ă���X�e�[�^�X�̏㏸
///// </summary>
//void StatusManager::UpSelectStatus(CharacterStatus* status)
//{
//	//�ŏI���肳��Ă�����
//	if (isFinalSelectStatus && lvUpCount != 0)
//	{
//		//�I�����Ă���X�e�[�^�X�̏㏸
//		switch (nowSelectStatus)
//		{
//		case static_cast<int>(SelectStatus::ATK):
//			status->ATK += LV_UP_ADD_VALUE;
//			break;
//		case static_cast<int>(SelectStatus::DEF):
//			status->DEF += LV_UP_ADD_VALUE;
//			break;
//		case static_cast<int>(SelectStatus::AGI):
//			status->AGI += LV_UP_ADD_VALUE;
//			break;
//		}
//		//�t���O��܂�
//		isFinalSelectStatus = false;
//		prevLv++;
//	}
//}
///// <summary>
///// �I�����ꂽ/����Ă��Ȃ��𓧖��x��ς��ĕ\��
///// </summary>
///// <param name="nowSelectStatus">���ݑI�𒆂̃X�e�[�^�X</param>
///// <param name="statusType">�X�e�[�^�X�̎��</param>
///// <param name="imgHandle"></param>
//void StatusManager::ChangeBlendRateDrawText(const int currentSelectStatus, const int statusType)
//{
//	const TCHAR* drawText = NULL;
//	switch (statusType)
//	{
//	case static_cast<int>(SelectStatus::ATK):
//		drawText = "ATK";
//		break;
//	case static_cast<int>(SelectStatus::DEF):
//		drawText = "DEF";
//		break;
//	case static_cast<int>(SelectStatus::AGI):
//		drawText = "AGI";
//		break;
//	}
//	// �J�[�\���ԍ����������Ƃ��͑I�����Ă���
//	// �I������Ă���Ƃ��͕��ʂɕ`�悷��
//	if (nowSelectStatus == statusType)
//	{
//		//���x���A�b�v���Ă�����button�摜��\������
//		DrawStringToHandle(STATUS_TEXT_POS[statusType].x, STATUS_TEXT_POS[statusType].y, drawText, FONT_COLOR_RED, statusFontHandle);
//	}
//	//�I������Ă��Ȃ��Ƃ��͏����Â��`�悷��
//	else
//	{
//		// ��I�����̉摜�̕`��i�I������Ă��Ȃ��摜�𔖂�����j
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
//		DrawStringToHandle(STATUS_TEXT_POS[statusType].x, STATUS_TEXT_POS[statusType].y, drawText, FONT_COLOR_RED, statusFontHandle);
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//	}
//}
//
///// <summary>
///// �A�C�R���̑I���i�J�[�\���̔ԍ���؂�ւ���j
///// </summary>
//void StatusManager::ChangeSelectStatus()
//{
//	// �L�[�̓��͏�Ԃ��Ƃ�
//	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//
//	//���
//	if (!isInputPad)
//	{
//		if (input & PAD_INPUT_UP)
//		{
//			switch (nowSelectStatus)
//			{
//			case static_cast<int>(SelectStatus::ATK):
//				nowSelectStatus = static_cast<int>(SelectStatus::ATK);
//				break;
//			case static_cast<int>(SelectStatus::DEF):
//				nowSelectStatus = static_cast<int>(SelectStatus::ATK);
//				break;
//			case static_cast<int>(SelectStatus::AGI):
//				nowSelectStatus = static_cast<int>(SelectStatus::DEF);
//				break;
//			}
//			isInputPad = true;
//		}
//		// ����
//		if (input & PAD_INPUT_DOWN)
//		{
//			switch (nowSelectStatus)
//			{
//			case static_cast<int>(SelectStatus::ATK):
//				nowSelectStatus = static_cast<int>(SelectStatus::DEF);
//				break;
//			case static_cast<int>(SelectStatus::DEF):
//				nowSelectStatus = static_cast<int>(SelectStatus::AGI);
//				break;
//			case static_cast<int>(SelectStatus::AGI):
//				nowSelectStatus = static_cast<int>(SelectStatus::AGI);
//				break;
//			}
//			isInputPad = true;
//		}
//	}
//	else
//	{
//		inputWaitTimer->StartTimer();
//	}
//	if (inputWaitTimer->CountTimer())
//	{
//		isInputPad = false;
//		inputWaitTimer->EndTimer();
//	}
//	// �ŏI�I��
//	if (input & PAD_INPUT_2)
//	{
//		isFinalSelectStatus = true;
//		isInputPad = true;
//	}
//}
