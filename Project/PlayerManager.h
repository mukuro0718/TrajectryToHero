//===========================================================================
//@brief �v���C���[�}�l�[�W���[�N���X / �Ǘ�
//===========================================================================
#pragma once
#include"DxLib.h"
#include"SwordGirl.h"
class PlayerManager
{
public:
	PlayerManager();//�R���X�g���N�^
	~PlayerManager();//�f�X�g���N�^

	void Init();//�������i�E�F�[�u�؂�ւ����Ɏg�p����j
	void Move(const VECTOR _cameraToPlayer);//�ړ�
	void Attack();//�U��
	void Update();//�X�V
	void Draw();//�`��
	void Final();//�폜
	void LvUP();
	//bool IsStoppingUpdate();
	//���W��getter
	const VECTOR GetPos() { return player->GetPos(); }
	//���f���n���h����getter
	const int GetModelHandle()const { return player->GetModelHandle(); }

private:
	int model;

	SwordGirl* player;
	bool isDrawImg;
};

