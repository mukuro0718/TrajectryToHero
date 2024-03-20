#pragma once
#include<DxLib.h>
#include<vector>
class FireParticle
{
public:
	FireParticle(const VECTOR _centerPos, const int _particleData);//�R���X�g���N�^
	~FireParticle();//�f�X�g���N�^

	const void Init();	//������
	const void Update();//�X�V
	const void Draw();	//�`��

private:
	/*�ÓI�萔*/
	static constexpr float	SIZE_REDUCED_VALUE	= 0.4f;	//�T�C�Y�����l
	static constexpr float	CX					= 0.5;	//CX
	static constexpr float	CY					= 0.5f;	//CY
	static constexpr float	ANGLE				= 0.0f;	//�A���O��
	static constexpr int	SIGN_RANGE			= 1;	//�����͈�
	static constexpr int	X_POS_RANGE			= 5;	//X�͈�
	static constexpr int	Z_POS_RANGE			= 5;	//Z�͈�
	static constexpr int	SPEED_RANGE			= 2;	//�����͈̔�
	static constexpr int	ALPHA_RANGE			= 255;	//�A���t�@�͈�
	static constexpr int	ALPHA_MAX_VALUE		= 255;	//�A���t�@�ő�l
	static constexpr int	ALPHA_REDUCED_VALUE = 10;	//�A���t�@�����l

	/*���������֐�*/
	const float ReturnRandomFloat(const bool _useSign, const int _range);//Float�^�̃����_����Ԃ�
	/*�����o�ϐ�*/
	VECTOR	centerPos;		//���S���W
	VECTOR	pos;			//���W
	float	size;			//�T�C�Y
	float	speed;			//����
	bool	isDraw;			//�`�悷�邩
	int		alpha;			//�A���t�@
    int		particleData;	//�p�[�e�B�N���摜
};

