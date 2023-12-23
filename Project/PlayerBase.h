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
class PlayerBase :public CharacterBase
{
public:
	PlayerBase(){};						//�R���X�g���N�^
	PlayerBase(const int _modelHandle);	// ��������R���X�g���N�^
	virtual ~PlayerBase();				// �f�X�g���N�^
	void Draw();						//�`��
	void Delete();						//�폜
	//���z�֐��i�p����Ŏ����j
	virtual void Update() = 0;			//�X�V
	virtual void Init() = 0;			//������

	bool IsStoppingUpdate();
	void CalcHP(const float _atk);//HP�v�Z
	void CalcExp(const float _expToGive);//���x���A�b�v����
	const float GetAtk();
	const float GetHp();
protected:
	/*�ÓI�萔*/
	static constexpr float WALK_SPEED = 5.0f;	//��������
	/*�����o�ϐ�*/
	CharacterStatus* status;			//�X�e�[�^�X
	VECTOR cameraToPlayer;
	BloodParticle* blood;//�����Ԃ��p�[�e�B�N��
private:
	/*�����o�ϐ�*/
	static constexpr float CAPSULE_HEIGHT = 30.0f;//�J�v�Z���̍���
	static constexpr float CAPSULE_RADIUS = 10.0f;//�J�v�Z���̔��a
	static const	 int   CAPSULE_COLOR;//�J�v�Z���̐F
	static constexpr float SPHERE_RADIUS = 20.0f;//�X�t�B�A�̔��a
	static const int SPHERE_COLOR;//�X�t�B�A�̐F
	static const VECTOR SPHERE_POS_OFFSET;//�X�t�B�A�I�t�Z�b�g
	static constexpr float INIT_DEGREES = 0.0f;//�����x��
	static constexpr float ADD_DEGREES_VALUE = 1.6f;//X�x��������
	static const VECTOR CENTER_POS_OFFSET;//���S���W�I�t�Z�b�g
	VECTOR centerPos;//���S���W
	float degrees;//�x��
	SwordTrail* swordTrail;//���̋O��
	Timer* attackLatency;//�U�����ҋ@����
};

