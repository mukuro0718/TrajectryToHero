//===============================================
// 覐΃N���X
// 覐Έ�̓������s��
//===============================================
#pragma once
#include<DxLib.h>
#include"Common.h"
class Shadow;
class MeteoriteBase
{
public:
	MeteoriteBase();//�R���X�g���N�^
	~MeteoriteBase();//�f�X�g���N�^

	void Init();//�X�V
	void Update();//�X�V
	void Draw(const int _stageModelHandle);//�`��
	const SphereInfo GetSphereInfo() { return sphereInfo; }
private:
	/*�ÓI�萔*/
	static constexpr int RADIUS_RANGE = 7;//���a�͈̔�
	static constexpr int SPEED_RANGE = 2;//�X�s�[�h�̑���
	static constexpr int DIV_NUM = 16;//��������
	static constexpr bool FILL_FLAG = true;//����h��Ԃ���
	static constexpr float RADIUS = 20.0f;
	static constexpr VECTOR POS_RANGE = { 450.0f,100.0f,500.0f };//�����_���ŏo�����W�͈̔�
	static constexpr VECTOR POS_OFFSET = { 0.0f,200.0f,0.0f };//���W�̕␳�l
	static constexpr float SHADOW_SIZE = 20.0f;
	static constexpr float SHADOW_HEIGHT = 1000.0f;

	static const int COLOR;//�F
	/*�����o�ϐ�*/
	SphereInfo sphereInfo;//�����\����
	Shadow* shadow;
	float speed;//����
};

