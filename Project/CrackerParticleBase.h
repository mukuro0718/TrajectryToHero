//========================================================
// @brief �X�e�[�^�X�㏸���p�[�e�B�N��
//========================================================
#pragma once
#include<DxLib.h>

class CrackerParticleBase
{
public:
	CrackerParticleBase(const int _color);	//�R���X�g���N�^
	~CrackerParticleBase();					//�f�X�g���N�^

	const void Init(const VECTOR _initPos);	//������
	const void Update();					//�X�V
	const void Draw();						//�`��
	const void OffIsDraw() { isDraw = false; }//�`��t���O������
private:
	/*�ÓI�萔*/
	static constexpr int	SIGN_RANGE		= 1;		//�����͈�
	static constexpr int	SIZE_RANGE		= 10;		//�傫���͈�
	static constexpr int	POS_RANGE		= 5;		//���W�͈�
	static constexpr int	SPEED_RANGE		= 10;		//�����͈̔�
	static constexpr int	X_LIMIT			= 900;		//�ő�X
	static constexpr int	MAX_FRAME_COUNT = 10;		//�ő�t���[��
	static constexpr float	Y_LIMIT			= 250.0f;	//�ő�Y
	/*���������֐�*/
	float ReturnRandomFloatValue(const bool _sign, const int _range);//�����_����Float�^�̒l��Ԃ�
	/*�����o�ϐ�*/
	VECTOR	initPos;			//�������W
	VECTOR	vertexPos1;			//�������_���W�P
	VECTOR	vertexPos2;			//�������_���W�Q
	VECTOR	vertexPos3;			//�������_���W�Q
	VECTOR	vertexPos2Offset;	//�������_�Q�␳���W
	VECTOR	vertexPos3Offset;	//�������_�R�␳���W
	VECTOR	moveVec;			//�ړ��x�N�g��
	float	speed;				//����
	float	size;				//�傫��
	float	count;				//�t���[���J�E���g
	bool	isDraw;				//�`�悵�Ă��邩
	int		color;				//�F
};

