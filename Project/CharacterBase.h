//===========================================================================
//@brief �L�����N�^�[�x�[�X�N���X
// �L�����N�^�[�I�u�W�F�N�g�ɕK���������Ă����������̂��`
//===========================================================================

#pragma once
#include<DxLib.h>
#include"Common.h"


class CharacterBase
{
public:
	CharacterBase();//�R���X�g���N�^
	virtual ~CharacterBase();//�f�X�g���N�^
	void SetUpCapsule(const VECTOR _pos,const float _height,const float _radius,const int _color,const int _flag);//�f�o�b�O�p�J�v�Z���̈ʒu�ݒ�
	void SetUpSphere(const VECTOR _pos, const float _radius, const int _color, const int _flag);//�f�o�b�O�p�X�t�B�A�̈ʒu�ݒ�
	void DrawCapsule(const CapsuleInfo _capsuleInfo);//�f�o�b�O�p�J�v�Z���̕`��
	void DrawSphere(const SphereInfo _sphereInfo);//�f�o�b�O�p�J�v�Z���̕`��
	//�|�W�V������getter/setter
	const VECTOR& GetPos() const { return pos; }
	//���f���n���h����getter
	const int GetModelHandle()const { return modelHandle; }

protected:
	/*�ÓI�萔*/
	static constexpr int INIT_MODELHANDLE = 0;
	/*�����o�ϐ�*/
	int				modelHandle;	//���f���n���h��
	VECTOR			pos;			//���W
	VECTOR			rotate;			//��]��
	VECTOR			scale;			//�X�P�[��
	CapsuleInfo		capsuleInfo;	//�J�v�Z�����
	SphereInfo		sphereInfo;		//�����
	bool			isHit       ;	//����������
	bool			isInvincible;   //���G���
	bool			isMove;			//�ړ�������
	bool			isAttack;		//�U��������
private:
	void Init();
};

