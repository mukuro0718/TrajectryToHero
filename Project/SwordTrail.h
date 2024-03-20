//===========================================================================
//@brief ��ʃu���[�N���X
// �Q�lURL https://haina.hatenablog.com/entry/2016/05/17/230902
// �ŏ��̍��W���Z�b�g���ꂽ��^�C�}�[���X�^�[�g������
// �^�C�}�[���ڕW���ԂɒB�����炻�̎��̍��W���܂��L������
// ���݂̋O�Ղ͕ۑ����Ă��钸�_�������Ȃ��A�p�΂��Ă��邽�߁A���Ԃ�����Ƃ���
// �X�v���C���Ȑ����g��
//===========================================================================
#pragma once
#include<DxLib.h>
#include<vector>

class Timer;

class SwordTrail
{
public:
	SwordTrail();	//�R���X�g���N�^
	~SwordTrail();	//�f�X�g���N�^

	const void Init();													//������
	const void Update(const VECTOR _topPos, const VECTOR _underPos);	//�X�V
	const void Draw();													//�`��
	const void Delete();												//�폜
	const void StartTimer();											//�^�C�}�[���n�߂�
	/*getter*/
	const bool GetIsStartTimer();
private:
	/*�ÓI�萔*/
	static constexpr int VERTEX_POS_NUM	 = 10;	//���_���W��
	static constexpr int MAX_ALPHA_VALUE = 100;	//�ő�A���t�@�l
	static constexpr int ADD_ALPHA_VALUE = 10;	//�A���t�@�l������

	static const VERTEX3D INIT_VERTEX;	//�������_���
	static const COLOR_U8 TRAIL_COLOR;	//�O�Ղ̐F
	static const VECTOR	  VERTEX_NORM;	//�@���x�N�g��
	
	/*���������֐�*/
	const VERTEX3D	SetVertexInfo(const VECTOR _pos);//���_���̐ݒ�
	const void		SetVertexAd();					 //���_�A�h���X�̐ݒ�
	const void		SetAlpha();						 //�A���t�@�l�̐ݒ�

	/*�����o�ϐ�*/
	Timer* drawTimer;//�`��p�^�C�}�[
	
	//���_�C���f�b�N�X�z��ւ̃A�h���X
	//�|���S����`�悷��Ƃ��ɁA���_���W�z��̂ǂ̒��_���g���̂������߂�
	//��F1�ԁA�Q�ԁA�R�Ԃ̒��_���g���Ƃ�
	//index[0] = 1,index[1] = 2,index[2] = 3
	std::vector<VERTEX3D> vertexInfo;	//���_���W
	std::vector<WORD>	  vertexIndexAd;//���_�C���f�b�N�X
	std::vector<int>	  alphaValue;	//�A���t�@�l
	
	bool isDraw;				//�`�悷�邩
	int	 frameCount;				//�A���t�@�l�����p�t���[���J�E���g
	int  vertexSetWaitFrameCount;//���_�ݒ�ҋ@����
	int  holdVertexNum;			//�ێ����Ă��钸�_��
	int  assignAd;				//�������A�h���X
	/*
	HAKC:
	<WORD>
	unsigned int�^ typedef�Ŗ��O����������
	����ɂ��,WORD�ł�unsigned int�����̕ϐ��Ƃ��Ďg����
	<COLOR_U8>
	unsigned char�^�̃J���[�l
	�ʏ��RGB�ɉ����A�����x��\���A���t�@�l���ݒ�ł���
	*/
};
