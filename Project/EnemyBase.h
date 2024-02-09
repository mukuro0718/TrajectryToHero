//===========================================================================
//@brief �G�l�~�[�x�[�X�N���X / ���
//===========================================================================
#pragma once
#include"CharacterBase.h"
#include"CharacterStatus.h"
#include"Common.h"
class Timer;
class BloodParticle;
class StrongerUI;

class EnemyBase:public CharacterBase 
{
public:
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
	const int GetModelHandle()const { return modelHandle; }

	const float GetHp()const { return status->GetHp(); }
	const float GetAtk()const { return status->GetAtk(); }
	float CalcHP(const float _atk, const VECTOR _attackerPos);//HP�v�Z
	void InitExpToGive();
	void ChangeColor();//�F�̕ύX

	const void DrawStrongerUI(const float _playerLv,const int _modelHandle, const int _frameNum);
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
	BloodParticle* blood;//�����Ԃ��p�[�e�B�N��
	CharacterStatus* status;
	StrongerUI* strongerUI;
	float maxHP;						//�ő�̗�
	bool isFarmBossEnemyPos;//�t�@�[�����{�X���W���Z�b�g���邩�ǂ���
	VECTOR bloodBaseDir;//�����Ԃ��p�[�e�B�N�����΂������̂��ƂɂȂ����
private:
	/*�萔*/
	static const COLOR_F CHANGE_DIF_COLOR;//�f�B�t���[�Y�J���[
	static const COLOR_F CHANGE_SPC_COLOR;//�X�y�L�����J���[
	static const COLOR_F CHANGE_EMI_COLOR;//�G�~�b�V�u�J���[
	static const COLOR_F CHANGE_AMB_COLOR;//�A���r�G���g�J���[

	static constexpr int RANDOM_X_RANGE = 300;		//�����W
	static constexpr int RANDOM_Z_RANGE = 300;		//�����W
	static constexpr int RANDOM_SIGN_RANGE = 1;		//����

	/*�����o�ϐ�*/
	bool isPrevColorChange;
	bool isChangeColor;//�F�̕ύX�����Ă��邩�ǂ���
	int materialNum;//�}�e���A���̐�
	Timer* changeColorTimer;//�F�ύX�^�C�}�[
	std::vector<COLOR_F> difColorInfo;//�f�B�t���[�Y�J���[���
	std::vector<COLOR_F> spcColorInfo;//�X�y�L�����J���[���
	std::vector<COLOR_F> emiColorInfo;//�G�~�b�V�u�J���[���
	std::vector<COLOR_F> ambColorInfo;//�A���r�G���g�J���[���
	//EffectManager* effectManager;//�G�t�F�N�g
};

