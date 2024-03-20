//===============================================
// @brief ���N���X
// �G�̃X�|�[���ʒu�ɕ`��
//===============================================

#pragma once
#include<DxLib.h>
class SmokeOnCircle
{
public:
	SmokeOnCircle(const int _graphHandle);	//�R���X�g���N�^
	~SmokeOnCircle();						//�f�X�g���N�^

	const void Init(const VECTOR _targetPos); //������
	const void Update();					  //�X�V
	const void Draw();						  //�`��
private:
	/*�ÓI�萔*/
	static constexpr float	INIT_SCALE			= 15.0f;//�������p�T�C�Y
	static constexpr int	MAX_SIZE			= 50;	//�ő�T�C�Y
	static constexpr int	INIT_ALPHA			= 130;	//�������p�A���t�@
	static constexpr int	MAX_ALPHA			= 255;	//�ő�A���t�@
	static constexpr int	MIN_ALPHA			= 0;	//�ŏ��A���t�@
	static constexpr int	MAX_REMOVE_ALPHA	= 5;	//�ő�폜�A���t�@
	/*���������֐�*/
	const void SetPosAndAlpha();												//���W�ƃA���t�@�̐ݒ�
	const float ReturnRandomFloatValue(const int _range, const bool _useSign);	//�����_����Float�^�̒l��n��
	
	/*�����o�ϐ�*/
	VECTOR	centerPos;	//���S���W
	VECTOR	pos;		//���W
	float	scale;		//�X�P�[��
	bool	isDrawStart;//�`�悪�n�܂��Ă��邩
	int		removeAlpha;//�����A���t�@
	int		alpha;		//�A���t�@
	int		handle;		//�摜�n���h��
};

