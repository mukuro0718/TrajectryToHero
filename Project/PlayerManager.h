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
	void Update(const VECTOR _cameraToPlayer);//�X�V
	void Draw();//�`��
	void Final();//�폜
	void LvUP();
	//bool IsStoppingUpdate();
	//���W��getter
	const VECTOR GetPos() { return player->GetPos(); }
	void SetPos(const VECTOR _set) { player->SetPos(_set); }
	//���f���n���h����getter
	const int GetModelHandle()const { return player->GetModelHandle(); }

private:
	int model;

	SwordGirl* player;
	bool isDrawImg;
};

