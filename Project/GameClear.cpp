////===========================================================================
////@brief �Q�[���N���A�N���X
//// �Q�[���N���A���̕`����s��
////===========================================================================
//#include "GameClear.h"
//#include "Common.h"
//#include "Animation.h"
//#include"Load.h"
//#include"Timer.h"
//
//
///// <summary>
///// �R���X�g���N�^
///// </summary>
//GameClear::GameClear()
//{
//	//������
//	Init();
//	//���[�h�N���X�̃C���X�^���X���擾
//	auto& load = Load::GetInstance();
//	//�摜�̃��[�h
//	load.GetGameClearData(&gameClearImageHandle);
//	//�쐬
//	Create();
//}
///// <summary>
///// �f�X�g���N�^
///// </summary>
//GameClear::~GameClear()
//{
//}
///// <summary>
///// ������
///// </summary>
//void GameClear::Init()
//{
//	gameClearImageHandle = 0;
//	gameClearImageAlpha  = 0;
//	isChangeAlphaValueSign = false;
//	isEndGameClearImage  = false;
//	isImageDrawingWait   = false;
//	imageDrawingWait	 = NULL;
//}
///// <summary>
///// �쐬
///// </summary>
//void GameClear::Create()
//{
//	imageDrawingWait = new Timer();
//	imageDrawingWait->Init(10);
//}
///// <summary>
///// ������
///// </summary>
//void GameClear::Final()
//{
//	DeleteGraph(gameClearImageHandle);
//	if (imageDrawingWait)
//	{
//		delete(imageDrawingWait);
//		imageDrawingWait = NULL;
//	}
//}
///// <summary>
///// �X�V
///// </summary>
//void GameClear::Update()
//{
//	//�Q�[���N���A�摜��`��
//	if (!isEndGameClearImage)
//	{
//		if (!isImageDrawingWait)
//		{
//			//���������ύX�t���O�������Ă�����A���t�@�l���}�C�i�X����
//			if (isChangeAlphaValueSign)
//			{
//				gameClearImageAlpha -= ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE;
//			}
//			//�����łȂ���΃v���X����
//			else
//			{
//				gameClearImageAlpha += ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE;
//			}
//
//			//�A���t�@�l���ő�l�����傫���Ȃ�����
//			if (gameClearImageAlpha >= MAX_GAME_CLEAR_IMAGE_ALPHA)
//			{
//				gameClearImageAlpha = MAX_GAME_CLEAR_IMAGE_ALPHA;
//				//�^�C�}�[���X�^�[�g������
//				imageDrawingWait->StartTimer();
//				//�^�C�}�[���X�^�[�g�����̂Ńt���O�𗧂Ă�
//				isImageDrawingWait = true;
//				//�A���t�@�l�����ύX�t���O�𗧂Ă�
//				isChangeAlphaValueSign = true;
//			}
//			//�A���t�@�l���ŏ��l�����������Ȃ�����
//			if (gameClearImageAlpha <= MIN_GAME_CLEAR_IMAGE_ALPHA)
//			{
//				//�t���O�𗧂Ă�
//				isEndGameClearImage = true;
//			}
//		}
//
//		//�����ҋ@�^�C�}�[���X�^�[�g���Ă��Ȃ�������
//		if (isImageDrawingWait)
//		{
//			//�����ҋ@�^�C�}�[���I�����Ă�����
//			if (imageDrawingWait->CountTimer())
//			{
//				//�^�C�}�[���I������
//				imageDrawingWait->EndTimer();
//				//�t���O������
//				isImageDrawingWait = false;
//			}
//		}
//	}
//}
///// <summary>
///// �`��
///// </summary>
//void GameClear::Draw()
//{
//	if (!isEndGameClearImage)
//	{
//		// ��I�����̉摜�̕`��i�I������Ă��Ȃ��摜�𔖂�����j
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gameClearImageAlpha);
//		DrawGraph(0, 0, gameClearImageHandle, TRUE);
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//	}
//}
