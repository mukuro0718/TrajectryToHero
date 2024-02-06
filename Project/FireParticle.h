#pragma once
#include<DxLib.h>
#include<vector>
class FireParticle
{
public:
	FireParticle(const VECTOR _centerPos, const int _particleData);//�R���X�g���N�^
	~FireParticle();//�f�X�g���N�^

	void Init();//������
	void Update();//�X�V
	void Draw();//�`��

private:
	/*�ÓI�萔*/
	static constexpr int SIGN_RANGE = 1;
	static constexpr int X_POS_RANGE = 5;
	static constexpr int Z_POS_RANGE = 5;
	static constexpr int SPEED_RANGE = 2;
	static constexpr float SIZE_REDUCED_VALUE = 0.4f;
	static constexpr int ALPHA_RANGE = 255; 
	static constexpr int ALPHA_MAX_VALUE = 255;
	static constexpr int ALPHA_REDUCED_VALUE = 10;

	static constexpr float CX = 0.5;
	static constexpr float CY = 0.5f;
	static constexpr float ANGLE = 0.0f;
	/*�����o�ϐ�*/
	VECTOR centerPos;//���S���W
	VECTOR pos;//���W
	float  size;//�T�C�Y
	float  speed;//����
	bool   isDraw;//�`�悷�邩
	int alpha;
    int particleData;
	float ReturnRandomFloat(const bool _useSign, const int _range);
};

