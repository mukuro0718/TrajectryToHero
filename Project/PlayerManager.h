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
	PlayerManager();	//�R���X�g���N�^
	~PlayerManager();	//�f�X�g���N�^

	const void Init();									//�������i�E�F�[�u�؂�ւ����Ɏg�p����j
	const void Move(const VECTOR _cameraToPlayer);		//�ړ�
	const void Attack();								//�U��
	const void Update();								//�X�V
	const void Draw(const VECTOR _bonfirePos);			//�`��
	const void DrawMenu();								//���j���[�̕\��
	const void Final();									//�폜
	const void StatusUpdate(const VECTOR _bonfirePos);	//�X�e�[�^�X�X�V
	const void FixMoveVec(const VECTOR _fixVec);		//�ړ��x�N�g���̏C��
	const void DrawShadow(const int _stageModelHandle);	//�e�̕`��
	const void CalcExp(const float _expToGive);			//�o���l�̌v�Z
	const void ReSpawn();								//���X�|�[��
	const void PhysicalRecovery();						//�̗͉�
	const void InitPos() const;							//���W�̏�����
	const void CalcHP(const float _atk, const VECTOR _attackerPos);//HP�v�Z

	/*HACK:
	const ~ ~()const��
	�ŏ���const = �萔�l��Ԃ�
	�Ō��const = ���̃����o�֐��͒l��������Ȃ�
	*/
	/*getter*/
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
	const void		  SetIsInvincible()			  { player->SetIsInvincible();			  }//���G�t���O��setter
	const void		  OnKnockBack(const VECTOR _targetVec) { player->OnKnockBack(_targetVec); }//�m�b�N�o�b�N�̊J�n
	const int		  GetModelHandle()		const { return player->GetModelHandle();	  }//���f���n���h����getter
	const int		  GetAtkUpCount()		const {	return player->GetAtkUpCount();		  }//�U���͏㏸�񐔂�getter
	const int		  GetAgiUpCount()		const {	return player->GetAgiUpCount();		  }//�f�����㏸�񐔂�getter
	const int		  GetDefUpCount()		const {	return player->GetDefUpCount();		  }//�h��͏㏸�񐔂�getter
	const int		  GetAttackNum()		const { return player->GetAttackNum();		  }//�U���ԍ��̕\��
private:
	/*�ÓI�萔*/
	static constexpr float SHADOW_SIZE	 = 20.0f;	//�e�̑傫��
	static constexpr float SHADOW_HEIGHT = 1000.0f;	//�e�̍���
	/*�����o�ϐ�*/
	SwordGirl*	 player;//�v���C���[�N���X
	OperationUI* opeUI;	//�������UI

	int model;		//���f���n���h��
	int frameImage;	//�t���[���摜
	int hpImage;	//HP�摜
	int expImage;	//EXP�摜
	int font;		//�t�H���g
	bool isDrawImg;	//�`�悵�Ă��邩
};

