#pragma once
#include<DxLib.h>
#include"Common.h"
class StatusUpParticleBase
{
public:
	StatusUpParticleBase(const int _imageHandle);//�R���X�g���N�^
	~StatusUpParticleBase();//�f�X�g���N�^

	void Init();
	void Update(const VECTOR _targetPos);//�X�V
	void Draw();//�`��
private:
	/*�ÓI�萔*/
	static constexpr int SIZE_RANGE = 5;
	static constexpr int SIGN_RANGE = 1;
	static constexpr int POS_RANGE = 10;
	static constexpr int SPEED_RANGE = 5;
	static constexpr int ALPHA_RANGE = 10;
	static constexpr int MAX_ALPHA_VALUE = 200;
	static constexpr int MIN_ALPHA_VALUE = 0;
	/*�����o�ϐ�*/
	int addAlphaValue;
	float size;
	VECTOR targetPos;
	VECTOR offsetPos;//�␳���W
	float speed;//����
	int alpha;
	int imageHandle;
	int frameCount;
	/*���������֐�*/
	float ReturnRandomFloatValue(const bool _sign, const int _range);//�����_����Float�^�̒l��Ԃ�
};

