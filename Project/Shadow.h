//========================================
// �e�N���X
// �v���C���[�ƃG�l�~�[�ɑ΂��Ċۉe�̕`����s��
//========================================

#pragma once
#include"DxLib.h"
#include<math.h>
class Shadow
{
public:
	Shadow();	//�R���X�g���N�^
	~Shadow();	//�f�X�g���N�^
	void Final();//�ŏI����
	void Draw(const int _stageModelHandle, const VECTOR _targetPos, const float _shadowHeight, const float _shadowSize);//�e��`��
private:
	int shadowHandle;//�e�摜�n���h��
};

