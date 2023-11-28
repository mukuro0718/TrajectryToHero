//===========================================================================
//@brief �X�e�[�W�؂�ւ��N���X
//===========================================================================
#include"StageChanger.h"
#include"Timer.h"
#include"Load.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
StageChanger::StageChanger()
{
	//������
	Init();
	//�摜�̃��[�h
	auto& load = Load::GetInstance();
	load.GetStageChangeData(&image);
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
StageChanger::~StageChanger()
{
	Delete();
}
/// <summary>
/// ������
/// </summary>
void StageChanger::Init()
{
	//�^�C�}�[�C���X�^���X�̍쐬
	StayMaxAlphaTimer = new Timer();
	//�ڕW���Ԃ̃Z�b�g
	StayMaxAlphaTimer->Init(SET_STAY_TIMER);
	//�A���t�@�l�̏�����
	alpha			= 0;
	backGroundAlpha = 0;
	alphaValue		= 6;
	//�E�F�[�u��ԊǗ��t���O
	isFarm			= true;//�t�@�[���X�e�[�W
	isBoss			= false;//�{�X�X�e�[�W
	isChangeStage	= true;
	isGameOver		= false;
	isGameClear		= false;
	isGameEnd		= false;
	isDrawBlackBack = false;
	isDrawAlert		= false;
}
/// <summary>
/// �X�e�[�W�؂�ւ����̉摜(FARM�ABOSS)�̕\��
/// </summary>
void StageChanger::DrawImageWhenSwitchingStage()
{
	//�X�e�[�W�؂�ւ��t���O�������Ă�����
	if (isChangeStage)
	{
		//�����A���t�@�l���ő�ɂȂ�����
		if (alphaValue > 0 && alpha >= 255)
		{
			//�^�C�}�[�̃X�^�[�g
			StayMaxAlphaTimer->StartTimer();

			//�^�C�}�[���ڕW���ԂɒB�����珈�����s��
			if (StayMaxAlphaTimer->CountTimer())
			{
				alphaValue = -6;
				StayMaxAlphaTimer->EndTimer();
			}
			//�҂��Ă��Ȃ�������
			else
			{
				alpha = 255;
			}
		}
		//�A���t�@�l�𑝂₷
		alpha += alphaValue;

		//�u�����h����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		//�`��摜�؂�ւ�
		if (isFarm)
		{
			DrawGraph(0, 0, image[static_cast<int>(ImageType::FARM_STAGE)], TRUE);
		}
		else if (isBoss)
		{
			DrawGraph(0, 0, image[static_cast<int>(ImageType::BOSS_STAGE)], TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�����A���t�@�l���O�����ɂȂ����烋�[�v�𔲂���
		if (alpha < 0)
		{
			alpha = 0;
			alphaValue = 6;
			isChangeStage = false;
		}
	}
}
/// <summary>
/// �Q�[���N���A�̉摜�̕\��
/// </summary>
void StageChanger::DrawGameClear()
{

}
/// <summary>
/// �폜
/// </summary>
void StageChanger::Delete()
{
	//for (int i = 0; i < IMAGE_NUM; i++)
	//{
	//	DeleteGraph(image[i]);
	//}
}
/// <summary>
/// �X�e�[�W�ړ����s�����ǂ���
/// </summary>
/// <param name="playerPos">�ύX�����v���C���[���W</param>
VECTOR StageChanger::DrawAlert(VECTOR playerPos)
{
	VECTOR outPutPos = playerPos;
	isChangeStage = true;
	isDrawAlert = true;
	DrawGraph(0, 0, image[static_cast<int>(ImageType::ALERT)], TRUE);
	int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (input & PAD_INPUT_2)
	{
		outPutPos = ORIGIN_POS;
		isFarm = false;
		isBoss = true;
		isDrawAlert = false;
	}
	else if (input & PAD_INPUT_3)
	{
		outPutPos.z = 450.0f;
		isChangeStage = false;
		isDrawAlert = false;
	}
	return outPutPos;
}