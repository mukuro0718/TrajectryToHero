//===========================================================================
//@brief �v���C���[�}�l�[�W���[�N���X / �Ǘ�
//===========================================================================
#pragma once
#include"DxLib.h"
#include"SwordGirl.h"
class OperationUI;

class PlayerManager
{
public:
	PlayerManager();//�R���X�g���N�^
	~PlayerManager();//�f�X�g���N�^

	void Init();//�������i�E�F�[�u�؂�ւ����Ɏg�p����j
	void Move(const VECTOR _cameraToPlayer);//�ړ�
	void Attack();//�U��
	void Update();//�X�V
	void Draw(const VECTOR _bonfirePos);//�`��
	const void DrawMenu();
	void Final();//�폜
	void StatusUpdate(const VECTOR _bonfirePos);//�X�e�[�^�X�X�V
	void FixMoveVec(const VECTOR _fixVec);
	void DrawShadow(const int _stageModelHandle);

	/*HACK:
	const ~ ~()const��
	�ŏ���const = �萔�l��Ԃ�
	�Ō��const = ���̃����o�֐��͒l��������Ȃ�
	*/
	
	const CapsuleInfo GetCapsuleInfo()		const { return player->GetCapsuleInfo();	  }//�J�v�Z������getter
	const SphereInfo  GetSphereInfo()		const { return player->GetSphereInfo();		  }//�J�v�Z������getter
	const VECTOR	  GetPos()				const { return player->GetPos();			  }//���W��getter
	const VECTOR	  GetMoveVec()			const { return player->GetMoveVec();		  }//�ړ��ʂ�getter
	const float		  GetAtk()				const { return player->GetAtk();			  }//�U���͂�getter
	const float		  GetHp()				const { return player->GetHp();				  }//�̗͂�getter
	const float		  GetLv()				const { return player->GetLv();				  }//LV��getter
	const bool		  GetIsInvincible()		const { return player->GetIsInvincible();	  }//���G�t���O��getter
	const bool		  GetIsAttack()			const { return player->GetIsAttack();		  }//�U���t���O��getter
	const bool		  GetIsDeath()			const { return player->GetIsDeath();		  }//���S�t���O��getter
	const bool		  GetIsShowStatusMenu()	const { return player->GetIsShowStatusMenu(); }//���x���A�b�v���j���[�̕\���t���O��getter
	const bool		  GetIsBonfireMenu()	const { return player->GetIsBonfireMenu();	  }//������΃��j���[�̕\���t���O��getter
	const bool		  GetIsHit()			const { return player->GetIsHit();			  }//�U���q�b�g�t���O��getter
	const void		  SetIsInvincible()			  { player->SetIsInvincible(); }
	const void		  OnKnockBack(const VECTOR _targetVec) { player->OnKnockBack(_targetVec); }//�m�b�N�o�b�N�̊J�n
	const int		  GetModelHandle()		const { return player->GetModelHandle();	  }//���f���n���h����getter
	const int		  GetAtkUpCount()		const {	return player->GetAtkUpCount();		  }//�U���͏㏸�񐔂�getter
	const int		  GetAgiUpCount()		const {	return player->GetAgiUpCount();		  }//�f�����㏸�񐔂�getter
	const int		  GetDefUpCount()		const {	return player->GetDefUpCount();		  }//�h��͏㏸�񐔂�getter
	const int GetAttackNum()const { return player->GetAttackNum(); }
	//�X�e�[�^�X����
	void CalcHP(const float _atk, const VECTOR _attackerPos);//HP�v�Z
	void CalcExp(const float _expToGive);
	void ReSpawn();//�̗͉�
	void PhysicalRecovery();//�̗͉�
	const void InitPos() const;
private:
	static constexpr float SHADOW_SIZE = 20.0f;
	static constexpr float SHADOW_HEIGHT = 1000.0f;
	int model;
	int frameImage;
	int hpImage;
	int expImage;
	SwordGirl* player;
	OperationUI* opeUI;
	int font;
	bool isDrawImg;
};

