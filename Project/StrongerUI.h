//==========================================================
//@brief ���GUI�N���X
//==========================================================
#pragma once
#include<DxLib.h>
class StrongerUI
{
public:
	StrongerUI();	//�R���X�g���N�^
	~StrongerUI();	//�f�X�g���N�^

	const void Update(const VECTOR _enemyPos, const int _modelHandle, const int _frameNum);	//�X�V
	const void Draw(const float _playerLv, const float _enemyLv) const;						//�`��
private:
	/*�����o�ϐ�*/
	VECTOR	pos;		//���W
	float	size;		//�T�C�Y
	float	angle;		//�A���O��
	int		imageHandle;//�摜�n���h��
};

