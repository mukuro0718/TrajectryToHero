//===========================================================================
//@brief �L�����N�^�[�x�[�X�N���X
// �L�����N�^�[�I�u�W�F�N�g�ɕK���������Ă����������̂��`
//===========================================================================

#pragma once
#include<DxLib.h>
#include"Common.h"

class Shadow;

class CharacterBase
{
public:
	CharacterBase();//�R���X�g���N�^
	virtual ~CharacterBase();//�f�X�g���N�^
	void SetUpCapsule(const VECTOR _pos,const float _height,const float _radius,const int _color,const int _flag);//�f�o�b�O�p�J�v�Z���̈ʒu�ݒ�
	void SetUpSphere(const VECTOR _pos, const float _radius, const int _color, const int _flag);//�f�o�b�O�p�X�t�B�A�̈ʒu�ݒ�
	void DrawCapsule(const CapsuleInfo _capsuleInfo);//�f�o�b�O�p�J�v�Z���̕`��
	void DrawSphere(const SphereInfo _sphereInfo);//�f�o�b�O�p�J�v�Z���̕`��
	void DrawShadow(const int _stageModelHandle, const VECTOR _targetPos, const float _shadowHeight, const float _shadowSize);//�e�̕`��
	//�|�W�V������getter/setter
	const VECTOR& GetPos() const { return pos; }
	//���f���n���h����getter
	const int GetModelHandle()const { return modelHandle; }
	//���G�t���O��getter
	const bool GetIsInvincible()const { return isInvincible; }
	//�J�v�Z������getter
	const CapsuleInfo GetCapsuleInfo()const { return capsuleInfo; }
	//������getter
	const SphereInfo GetSphereInfo()const { return sphereInfo; }
	//���S�t���O��getter
	const bool GetIsDeath()const { return isDeath; }
	//�ړ��ʂ�getter
	const VECTOR GetMoveVec()const { return moveVec; }
	const int GetAttackNum()const { return attackNum; }
protected:
	/*�ÓI�萔*/
	static constexpr int INIT_MODELHANDLE = 0;
	/*�����o�ϐ�*/
	int				modelHandle;	//���f���n���h��
	VECTOR			pos;			//���W
	VECTOR			moveVec;		//�ړ���
	VECTOR			rotate;			//��]��
	VECTOR			scale;			//�X�P�[��
	CapsuleInfo		capsuleInfo;	//�J�v�Z�����
	SphereInfo		sphereInfo;		//�����
	bool			isHit       ;	//����������
	bool			isInvincible;   //���G���
	bool			isMove;			//�ړ�������
	bool			isAttack;		//�U��������
	bool			isDeath;
	Shadow* shadow;
	int attackNum;//�U����
	/*HACK:�U�����邽�тɍU���J�E���g�𗧂ĂāA�U�����q�b�g������q�b�g�������ɍU���J�E���g���L�^����
	�����ē��������̎��͓����蔻����s��Ȃ��悤�ɂ���*/
private:
	void Init();
};

