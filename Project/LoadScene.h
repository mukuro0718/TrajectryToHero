//=============================================
//���[�h��ʃN���X
// 5�̒��_��ێ����ADrawLine�Ő���`�悷��
// �܂����_�̈ʒu���ړ������A�����Ă��邱�Ƃ�\���B
//=============================================
#pragma once
#include<DxLib.h>
#include<vector>

class LoadScene
{
public:
	LoadScene();//�R���X�g���N�^
	~LoadScene();//�f�X�g���N�^

	const void Init();//������
	const void Final();//�ŏI����
	const void Update();//�X�V
	const void Draw();//�`��
private:
	/*�ÓI�萔*/
	static constexpr int ADD_ALPHA					 = 1;	//�ǉ��A���t�@
	static constexpr int MAX_ALPHA					 = 255;	//�ő�A���t�@
	static constexpr int MIN_ALPHA					 = 0;	//�ŏ��A���t�@
	static constexpr int FONT_SIZE					 = 32;	//�t�H���g�̑傫��
	static constexpr int MAX_IS_INC_WAIT_FRAME_COUNT = 60;	//�ő�t���[���J�E���g
	static constexpr int MAX_UPDATE_WAIT_FRAME_COUNT = 80;	//�ő�t���[���J�E���g
	static constexpr int X							 = 1620;//�w���W
	static constexpr int Y							 = 980;	//�x���W

	static const int FONT_COLOR;//�t�H���g�̐F

	/*�����o�ϐ�*/
	int alpha;					//�A���t�@
	int isIncWaitFrameCount;	//�t���[���J�E���g
	int updateWaitFrameCount;	//�t���[���J�E���g
	bool isIncTheValue;			//�l���������Ă��邩(TRUE:���� FALSE:���� )
};

