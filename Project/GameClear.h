//===========================================================================
//@brief �Q�[���N���A�N���X
// �Q�[���N���A���̕`����s��
//===========================================================================
#pragma once
#include "DxLib.h"

class Animation;
class Timer;
class GameClear
{
public:

	GameClear();	// �R���X�g���N�^
	~GameClear();	// �f�X�g���N�^

	void Init();	//������
	void Final();	//�ŏI����
	void Update();	//�X�V
	void Draw();	//�`��

	const bool GetIsEndGameClearImage()const { return isEndGameClearImage; }
private:
	/*�萔*/
	static constexpr int MAX_GAME_CLEAR_IMAGE_ALPHA = 255;	//�ő�Q�[���N���A�摜�A���t�@�l
	static constexpr int MIN_GAME_CLEAR_IMAGE_ALPHA = 0;	//�ŏ��Q�[���N���A�摜�A���t�@�l
	static constexpr int ADD_GAME_CLEAR_IMAGE_ALPHA_VALUE = 2;//�Q�[���N���A�摜�A���t�@�l������
	/*�N���X*/
	Timer* imageDrawingWait;//�摜�`��ҋ@����
	/*���������֐�*/
	void Create();//�쐬
	/*�ϐ�*/
	int gameClearImageHandle;//�Q�[���N���A�摜�n���h��
	int gameClearImageAlpha;//�Q�[���N���A�摜�A���t�@�l
	int  addGameOverImageAlphaValue;	//�Q�[���I�[�o�[�摜�A���t�@�l������
	bool isChangeAlphaValueSign;//�A���t�@�l�����ύX�t���O�itrue:�[ false:�{�j
	bool isEndGameClearImage;//�Q�[���N���A�摜���I��������(true:�I�����Ă��� false:�I�����Ă��Ȃ�)
	bool isImageDrawingWait;//�摜�`��ҋ@���ԃ^�C�}�[���X�^�[�g������(true:�X�^�[�g���Ă��� false:�X�^�[�g���Ă��Ȃ�)
	VECTOR playerPos;
};
