//===========================================================================
//@brief �X�e�[�^�X�N���X
//===========================================================================
#include"CharacterStatus.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CharacterStatus::CharacterStatus()
{

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
CharacterStatus::~CharacterStatus()
{

}
/// <summary>
/// �G���G�X�e�[�^�X�̏����ݒ�
/// </summary>
void CharacterStatus::InitWeakEnemyStatus()
{
	lv = 10.0f;			//���x���̃Z�b�g
	hp = 50.0f;		//�̗͂̃Z�b�g
	atk = 10.0f;			//�U���͂̃Z�b�g
	def = 50.0f;			//�h��͂̃Z�b�g
	agi = 1.0f;			//�f�����̃Z�b�g
	expToGive = 50.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp = 0.0f;			//�o���l�̃Z�b�g
	needExp = 0.0f;
	maxHp = hp;
}
/// <summary>
/// ���{�X�X�e�[�^�X�̏����ݒ�
/// </summary>
void CharacterStatus::InitStrongEnemyStatus()
{
	lv = 10.0f;			//���x���̃Z�b�g
	hp = 100.0f;		//�̗͂̃Z�b�g
	atk = 20.0f;			//�U���͂̃Z�b�g
	def = 60.0f;			//�h��͂̃Z�b�g
	agi = 2.0f;			//�f�����̃Z�b�g
	expToGive = 150.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp = 0;			//�o���l�̃Z�b�g
	needExp = 0.0f;
	maxHp = hp;
}
/// <summary>
/// �{�X�X�e�[�^�X�̏����ݒ�
/// </summary>
void CharacterStatus::InitBossEnemyStatus()
{
	lv			= 10.0f;	//���x���̃Z�b�g
	hp			= 300.0f;	//�̗͂̃Z�b�g
	atk			= 30.0f;	//�U���͂̃Z�b�g
	def			= 70.0f;	//�h��͂̃Z�b�g
	agi			=2.0f;		//�f�����̃Z�b�g
	expToGive = 100.0f;		//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp			= 0.0f;		//�o���l�̃Z�b�g
	needExp = 0.0f;
	maxHp = hp;
}

/// <summary>
/// �v���C���[�X�e�[�^�X�̏����ݒ�
/// </summary>
void CharacterStatus::InitPlayerStatus()
{
	lv			 = 1.0f;	//���x���̃Z�b�g
	hp			 = 30.0f;	//�̗͂̃Z�b�g
	atk		 = 3.0f;	//�U���͂̃Z�b�g
	def		 = 1.0f;	//�h��͂̃Z�b�g
	agi		 = 1.5f;	//�f�����̃Z�b�g
	expToGive = 0.0f;	//�|���ꂽ�Ƃ��^����o���l�̃Z�b�g
	exp		 = 0.0f;	//�o���l�̃Z�b�g
	needExp = 0.0f;
	maxHp = hp;
}

/// <summary>
/// HP�v�Z
/// </summary>
void CharacterStatus::CalcHP(const float _atk)
{
	hp -= atk * def * 0.05f;
}