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

protected:
	/*�ÓI�萔*/
	static constexpr float WALK_SPEED = 5.0f;	//��������
	static constexpr int INIT_MODELHANDLE = 0;
	/*�����o�ϐ�*/
	VECTOR			hitCheckAttack;	//�U���������蔻��
	CharacterStatus* status;			//�X�e�[�^�X

private:
	/*�����o�ϐ�*/
	static constexpr float CAPSULE_HEIGHT = 30.0f;
	static constexpr float CAPSULE_RADIUS = 10.0f;
	static const	 int   CAPSULE_COLOR;
};

