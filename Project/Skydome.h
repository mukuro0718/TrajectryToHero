//===========================================================================
//@brief �X�J�C�h�[���N���X
// �X�J�C�h�[���̕`����s��
//===========================================================================

#pragma once
#include"DxLib.h"
#include"Common.h"

class Skydome
{
public:
	Skydome();//�R���X�g���N�^
	~Skydome();//�f�X�g���N�^

	void Init();//������
	void Draw();//�`��
private:
	/*�ÓI�萔*/
	static const VECTOR SCALE;
	/*�����o�ϐ�*/
	VECTOR pos;
	int modelHandle;
};

