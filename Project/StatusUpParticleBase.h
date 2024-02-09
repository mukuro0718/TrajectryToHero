#pragma once
#include<DxLib.h>
class StatusUpParticleBase
{
public:
	StatusUpParticleBase(const int _color);//�R���X�g���N�^
	~StatusUpParticleBase();//�f�X�g���N�^

	void Init();
	void Update(const VECTOR _targetPos);//�X�V
	void Draw();//�`��
private:
	/*�ÓI�萔*/
	static constexpr int SIZE_RANGE = 5;
	static constexpr int SIGN_RANGE = 1;
	static constexpr int POS_RANGE = 10;
	static constexpr int SPEED_RANGE = 9;
	static constexpr int MAX_ALPHA_VALUE = 200;
	static constexpr int MIN_ALPHA_VALUE = 0;
	static constexpr int ADD_ALPHA_VALUE = 5;
	/*�����o�ϐ�*/
	VECTOR topPos;//����W
	VECTOR underPos;//�������W
	VECTOR offsetPos;//�␳���W
	float size;//�T�C�Y
	float speed;//����
	int color;
	int alpha;
	/*���������֐�*/
	float ReturnRandomFloatValue(const bool _sign, const int _range);//�����_����Float�^�̒l��Ԃ�
};

