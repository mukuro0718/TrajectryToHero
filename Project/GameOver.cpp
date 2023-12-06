//===========================================================================
//@brief �Q�[���I�[�o�[�N���X
// �Q�[���I�[�o�[���̕`����s��
//===========================================================================
#include "GameOver.h"
#include "Common.h"
#include "Animation.h"
#include"Load.h"
#include"Timer.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
GameOver::GameOver()
{
	//������
	Init();
	//���[�h�N���X�̃C���X�^���X���擾
	auto& load = Load::GetInstance();
	//�摜�̃��[�h
	load.GetGameOverData(&gameOverImageHandle);
	//�쐬
	Create();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
GameOver::~GameOver()
{
}
/// <summary>
/// ������
/// </summary>
void GameOver::Init()
{
	gameOverImageHandle = 0;
	gameOverImageAlpha = 0;
	addGameOverImageAlphaValue = 1;
	isEndGameOverImage = false;
	isImageDrawingWait = false;
	imageDrawingWait = NULL;
}
/// <summary>
/// �쐬
/// </summary>
void GameOver::Create()
{
	imageDrawingWait = new Timer();
	imageDrawingWait->Init(10);
}
/// <summary>
/// ������
/// </summary>
void GameOver::Final()
{
	DeleteGraph(gameOverImageHandle);
	if (imageDrawingWait)
	{
		delete(imageDrawingWait);
		imageDrawingWait = NULL;
	}
}
/// <summary>
/// �X�V
/// </summary>
void GameOver::Update()
{
	//�Q�[���N���A�摜��`��
	if (!isEndGameOverImage)
	{
		//�����ҋ@�^�C�}�[���X�^�[�g���Ă��Ȃ�������
		if (!isImageDrawingWait)
		{
			//���������ύX�t���O�������Ă�����A���t�@�l���}�C�i�X����
			if (isChangeAlphaValueSign)
			{
				gameOverImageAlpha -= ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE;
			}
			//�����łȂ���΃v���X����
			else
			{
				gameOverImageAlpha += ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE;
			}

			//�A���t�@�l���ő�l�����傫���Ȃ�����
			if (gameOverImageAlpha >= MAX_GAME_CLEAR_IMAGE_ALPHA)
			{
				gameOverImageAlpha = MAX_GAME_CLEAR_IMAGE_ALPHA;
				//�^�C�}�[���X�^�[�g������
				imageDrawingWait->StartTimer();
				//�^�C�}�[���X�^�[�g�����̂Ńt���O�𗧂Ă�
				isImageDrawingWait = true;
				//�A���t�@�l�����ύX�t���O�𗧂Ă�
				isChangeAlphaValueSign = true;
			}
			//�A���t�@�l���ŏ��l�����������Ȃ�����
			if (gameOverImageAlpha <= MIN_GAME_CLEAR_IMAGE_ALPHA)
			{
				//�t���O�𗧂Ă�
				isEndGameOverImage = true;
			}
		}

		//�����ҋ@�^�C�}�[���X�^�[�g���Ă��Ȃ�������
		if (isImageDrawingWait)
		{
			//�����ҋ@�^�C�}�[���I�����Ă�����
			if (imageDrawingWait->CountTimer())
			{
				//�^�C�}�[���I������
				imageDrawingWait->EndTimer();
				//�t���O������
				isImageDrawingWait = false;
			}
		}
	}
}
/// <summary>
/// �`��
/// </summary>
void GameOver::Draw()
{
	if (!isEndGameOverImage)
	{
		// ��I�����̉摜�̕`��i�I������Ă��Ȃ��摜�𔖂�����j
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gameOverImageAlpha);
		DrawGraph(0, 0, gameOverImageHandle, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
