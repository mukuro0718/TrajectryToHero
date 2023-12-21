//===========================================================================
//@brief �G�l�~�[�x�[�X�N���X / ���
//===========================================================================
#pragma once
#include"CharacterBase.h"
#include"CharacterStatus.h"
#include"Common.h"
//class EffectManager;
//class CharacterStatus;

class EnemyBase:public CharacterBase 
{
public:
	EnemyBase(){}						// �R���X�g���N�^
	EnemyBase(int _modelHandle);	// ��������R���X�g���N�^
	virtual ~EnemyBase();				// �f�X�g���N�^

	void Draw(VECTOR _playerPos);	//�`��
	void Final();					//�폜
	void FixMoveVec(const VECTOR _fixVec);

	//���z�֐��i�p����Ŏ����j
	virtual void Update() = 0;	//�X�V
	virtual void Init() = 0;					//������
	virtual void Move(const VECTOR _playerPos) = 0;	//�ړ�

	//�|�W�V������getter/setter
	const VECTOR& GetPos() const { return pos; }
	////�����蔻���setter
	const bool GetIsDeath()const { return isDeath; }
	const bool GetIsAttack()const { return isAttack; }
	//���a��setter
	const float GetRadius()const { return RADIUS; }
	const int GetModelHandle()const { return modelHandle; }

	const float GetHp()const { return status->GetHp(); }
	const float GetAtk()const { return status->GetAtk(); }
	float CalcHP(const float _atk);//HP�v�Z
	void InitExpToGive();
	void ChangeColor();//�F�̕ύX
protected:
	enum class RandomSign
	{
		PLUS,//�{
		MINUS,//�[
	};
	/*�ÓI�萔*/
	static constexpr int RANDOM_RANGE = 7;//�����_���Ő�������l�͈̔�
	static const VECTOR  DESTROY_POS;			//HP���O�ɂȂ����Ƃ����̍��W�ɍs��
	VECTOR spawnPos;
	//���������֐�
	void RandomWalk();
	/*�����o�ϐ�*/

	CharacterStatus* status;
	float maxHP;						//�ő�̗�
	bool isFarmBossEnemyPos;//�t�@�[�����{�X���W���Z�b�g���邩�ǂ���
private:
	/*�萔*/
	static const COLOR_F CHANGE_DIF_COLOR;//�f�B�t���[�Y�J���[
	static const COLOR_F CHANGE_SPC_COLOR;//�X�y�L�����J���[
	static const COLOR_F CHANGE_EMI_COLOR;//�G�~�b�V�u�J���[
	static const COLOR_F CHANGE_AMB_COLOR;//�A���r�G���g�J���[

	static constexpr int RANDOM_X_RANGE = 300;		//�����W
	static constexpr int RANDOM_Z_RANGE = 300;		//�����W
	static constexpr int RANDOM_SIGN_RANGE = 1;		//����
	static constexpr float RADIUS = 5.0f;	//�J�v�Z���̔��a
	static constexpr float HEIGHT = 30.0f;	//�J�v�Z���̍���
	static const int CAPSULE_COLOR;			//�J�v�Z���̐F
	static constexpr float SPHERE_RADIUS = 3.0f;	//���̔��a
	static const int SPHERE_COLOR;					//���̐F

	/*�����o�ϐ�*/
	bool isChangeColor;//�F�̕ύX�����Ă��邩�ǂ���
	int materialNum;//�}�e���A���̐�
	std::vector<COLOR_F> difColorInfo;//�f�B�t���[�Y�J���[���
	std::vector<COLOR_F> spcColorInfo;//�X�y�L�����J���[���
	std::vector<COLOR_F> emiColorInfo;//�G�~�b�V�u�J���[���
	std::vector<COLOR_F> ambColorInfo;//�A���r�G���g�J���[���
	//EffectManager* effectManager;//�G�t�F�N�g
};

