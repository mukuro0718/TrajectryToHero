////===========================================================================
////@brief �Q�[���I�[�o�[�N���X
//// �Q�[���I�[�o�[���̕`����s��
////===========================================================================
//#pragma once
//#include "DxLib.h"
//#include<vector>
//
//class Timer;
//
//using namespace std;
//
//class GameOver
//{
//public:
//
//	GameOver();	// �R���X�g���N�^
//	~GameOver();	// �f�X�g���N�^
//
//	void Init();	//������
//	void Final();	//�ŏI����
//	void Update();	//�X�V
//	void Draw();	//�`��
//
//	const bool GetIsEndGameOverImage()const { return isEndGameOverImage; }
//private:
//	static constexpr int MAX_GAME_CLEAR_IMAGE_ALPHA = 255;	//�ő�Q�[���N���A�摜�A���t�@�l
//	static constexpr int MIN_GAME_CLEAR_IMAGE_ALPHA = 0;	//�ŏ��Q�[���N���A�摜�A���t�@�l
//	static constexpr int ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE = 2;//�Q�[���N���A�摜�A���t�@�l������
//	Timer* imageDrawingWait;	//�摜�`��ҋ@����
//	/*���������֐�*/
//	void Create();//�쐬
//	/*�ϐ�*/
//	int  gameOverImageHandle;			//�Q�[���I�[�o�[�摜�n���h��
//	int  gameOverImageAlpha;			//�Q�[���I�[�o�[�摜�A���t�@�l
//	int  addGameOverImageAlphaValue;	//�Q�[���I�[�o�[�摜�A���t�@�l������
//	bool isChangeAlphaValueSign;		//�A���t�@�l�����ύX�t���O�itrue:�[ false:�{�j
//	bool isEndGameOverImage;			//�Q�[���I�[�o�[�摜���I��������(true:�I�����Ă��� false:�I�����Ă��Ȃ�)
//	bool isImageDrawingWait;			//�摜�`��ҋ@���ԃ^�C�}�[���X�^�[�g������(true:�X�^�[�g���Ă��� false:�X�^�[�g���Ă��Ȃ�)
//};
