#pragma once
#include<DxLib.h>
#include "Common.h"
class Explosion
{
public:
	Explosion();//�R���X�g���N�^
	~Explosion();//�f�X�g���N�^
	void Init();//������
	void Update(const bool _isDraw, const VECTOR _targetPos);//�X�V
	void Draw();//�`��
	const SphereInfo GetSphereInfo() { return sphereInfo; }
private:
	/*�ÓI�萔*/
	static constexpr float MAX_RADIUS_RANGE = 100.0f;//�ő唼�a�͈�
	static constexpr float MIN_RADIUS_RANGE = 0.0f;//�ŏ����a�͈�
	static constexpr float ADD_RADIUS_VALUE = 0.25f;//���a������
	static constexpr int MAX_ALPHA_VALUE = 255;//�ő�A���t�@�l
	static constexpr int MIN_ALPHA_VALUE = 0;//�ŏ��A���t�@�l
	static constexpr int ADD_ALPHA_VALUE = 5;//�A���t�@������
	static constexpr int DIV_NUM = 16;//���̕�����
	static constexpr bool FILL_FLAG = true;//�`�悷�鋅��h��Ԃ����ǂ���
	static const int COLOR;
	/*�����o�ϐ�*/
	SphereInfo sphereInfo;
	int alpha;//�A���t�@�l
	bool isDraw;//�`�悵�Ă��邩
	bool isInit;//������������
};

