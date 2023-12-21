//===========================================================================
//@brief �v���C���[�}�l�[�W���[�N���X / �Ǘ�
//===========================================================================
#pragma once
#include"DxLib.h"
#include"SwordGirl.h"
class BlurScreen;

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
	void StatusUpdate();//�X�e�[�^�X�X�V
	void FixMoveVec(const VECTOR _fixVec);
	void DrawShadow(const int _stageModelHandle);
	//bool IsStoppingUpdate();
	//���W��getter
	const VECTOR GetPos() { return player->GetPos(); }
	//���f���n���h����getter
	const int GetModelHandle()const { return player->GetModelHandle(); }
	//���G�t���O��getter
	const bool GetIsInvincible()const { return player->GetIsInvincible(); }
	//�J�v�Z������getter
	const CapsuleInfo GetCapsuleInfo()const { return player->GetCapsuleInfo(); }
	//������getter
	const SphereInfo GetSphereInfo()const { return player->GetSphereInfo(); }
	//�U���t���O��getter
	const bool GetIsAttack()const { return player->GetIsAttack(); }
	//���S�t���O��getter
	const bool GetIsDeath()const { return player->GetIsDeath(); }
	//�U���͂�getter
	const float GetAtk()const { return player->GetAtk(); }
	const float GetHp()const { return player->GetHp(); }
	const bool GetIsShowStatusMenu() { return player->GetIsShowStatusMenu(); }
	//�ړ��ʂ�getter
	const VECTOR GetMoveVec()const { return player->GetMoveVec(); }
	/*HACK:
	const ~ ~()const��
	�ŏ���const = �萔�l��Ԃ�
	�Ō��const = ���̃����o�֐��͒l��������Ȃ�
	*/
	//HP�v�Z
	void CalcHP(const float _atk);
	//���x���A�b�v����
	void CalcExp(const float _expToGive);
private:
	static constexpr float SHADOW_SIZE = 20.0f;
	static constexpr float SHADOW_HEIGHT = 1000.0f;
	int model;
	int frameImage;
	int hpImage;
	int expImage;
	SwordGirl* player;

	bool isDrawImg;
};

