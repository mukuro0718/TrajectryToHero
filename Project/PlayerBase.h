//===========================================================================
//@brief �v���C���[�x�[�X�N���X
//���f���̕`��ƃR�s�[�������f���̃A�����[�h���s��
//===========================================================================
#pragma once
#include"DxLib.h"
#include"CharacterBase.h"
class StatusManager;
class EffectManager;
class CharacterStatus;
class Timer;
class SwordTrail;
class BloodParticle;
class StatusUI;

class PlayerBase :public CharacterBase
{
public:
	PlayerBase(const int _modelHandle);	// ��������R���X�g���N�^
	virtual ~PlayerBase();				// �f�X�g���N�^
	const void Draw();						//�`��
	const void Delete();						//�폜
	//���z�֐��i�p����Ŏ����j
	virtual const void Update() = 0;			//�X�V
	virtual const void Init() = 0;			//������

	const void CalcHP(const float _atk, const VECTOR _attackerPos);//HP�v�Z
	const void CalcExp(const float _expToGive);//���x���A�b�v����
	const float GetAtk();
	const float GetHp();
	const float GetLv();
	const void TutorialStatusReset();
protected:
	/*�ÓI�萔*/
	static constexpr float WALK_SPEED = 5.0f;	//��������
	/*�����o�ϐ�*/
	CharacterStatus*	status;		//�X�e�[�^�X
	BloodParticle*		blood;		//�����Ԃ��p�[�e�B�N��
	SwordTrail*			swordTrail;	//���̋O��

	VECTOR	cameraToPlayer;			//�J��������v���C���[�ւ̃x�N�g��
	VECTOR	bloodBaseDir;			//�����Ԃ��p�[�e�B�N���̕����̂��ƂɂȂ����
	bool	isAttackReadying;		//�U������
	int		waitAttackFrameCount;	//�U���ҋ@�t���[���J�E���g��
private:
	/*�ÓI�萔*/
	static constexpr float	CAPSULE_HEIGHT		= 30.0f;//�J�v�Z���̍���
	static constexpr float	CAPSULE_RADIUS		= 10.0f;//�J�v�Z���̔��a
	static constexpr float	SPHERE_RADIUS		= 20.0f;//�X�t�B�A�̔��a
	static constexpr float	INIT_DEGREES		= 0.0f;	//�����x��
	static constexpr float	ADD_DEGREES_VALUE	= 1.6f;	//X�x��������

	static const	 int	SPHERE_COLOR;				//�X�t�B�A�̐F
	static const	 int	CAPSULE_COLOR;				//�J�v�Z���̐F
	static const	 VECTOR SPHERE_POS_OFFSET;			//�X�t�B�A�I�t�Z�b�g
	static const	 VECTOR CENTER_POS_OFFSET;			//���S���W�I�t�Z�b�g
	/*�����o�ϐ�*/
	StatusUI* statusUI;	//�X�e�[�^�XUI

	VECTOR	centerPos;	//���S���W
	float	degrees;	//�x��
};

