//=======================================================
// @brief�@���x���A�b�v�EHP�񕜎��p�[�e�B�N��
//=======================================================
#pragma once
#include<DxLib.h>
#include"Common.h"
class StatusUpParticleBase
{
public:
	StatusUpParticleBase(const int _imageHandle);	//�R���X�g���N�^
	~StatusUpParticleBase();						//�f�X�g���N�^

	const void Init();							//������
	const void Update(const VECTOR _targetPos);	//�X�V
	const void Draw();							//�`��
private:
	/*�ÓI�萔*/
	static constexpr int SIZE_RANGE		 = 5;	//�T�C�Y�͈�
	static constexpr int SIGN_RANGE		 = 1;	//�����͈�
	static constexpr int POS_RANGE		 = 10;	//���W�͈�
	static constexpr int SPEED_RANGE	 = 5;	//�X�s�[�h�͈�
	static constexpr int ALPHA_RANGE	 = 10;	//�A���t�@�͈�
	static constexpr int MAX_ALPHA_VALUE = 200;	//�ő�A���t�@
	static constexpr int MIN_ALPHA_VALUE = 0;	//�ŏ��A���t�@
	/*���������֐�*/
	const float ReturnRandomFloatValue(const bool _sign, const int _range);//�����_����Float�^�̒l��Ԃ�
	/*�����o�ϐ�*/
	VECTOR	targetPos;		//�ڕW���W
	VECTOR	offsetPos;		//�␳���W
	float	size;			//�T�C�Y
	float	speed;			//����
	int		addAlphaValue;	//�ǉ��A���t�@
	int		alpha;			//�A���t�@
	int		imageHandle;	//�摜�n���h��
	int		frameCount;		//�t���[���J�E���g
};

