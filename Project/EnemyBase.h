//===========================================================================
//@brief �G�l�~�[�x�[�X�N���X
//===========================================================================
#pragma once
#include"CharacterBase.h"
#include"CharacterStatus.h"
#include"Common.h"
class Timer;
class BloodParticle;
class StrongerUI;
class SpawnParticle;

class EnemyBase:public CharacterBase 
{
public:
	EnemyBase(const int _modelHandle);	// ��������R���X�g���N�^
	virtual ~EnemyBase();				// �f�X�g���N�^

	const void Draw(const VECTOR _playerPos);	//�`��
	const void Final();					//�폜
	const void FixMoveVec(const VECTOR _fixVec);

	//���z�֐��i�p����Ŏ����j
	virtual const void Update() = 0;	//�X�V
	virtual const void Init() = 0;					//������
	virtual const void Move(const VECTOR _playerPos) = 0;	//�ړ�

	const float CalcHP(const float _atk, const VECTOR _attackerPos);//HP�v�Z
	const void InitExpToGive();//�o���l�̏�����
	const void ChangeColor();//�F�̕ύX
	const void DrawStrongerUI(const float _playerLv,const int _modelHandle, const int _frameNum);//���G�}�[�N�̕`��

	//getter/setter
	const VECTOR GetPos			()const { return pos;				}//���W��getter
	const float  GetHp			()const { return status->GetHp();	}//�X�e�[�^�X�N���X�̗̑͂�getter
	const float  GetAtk			()const { return status->GetAtk();	}//�X�e�[�^�X�N���X�̍U���͂�getter
	const bool	 GetIsDeath		()const { return isDeath;			}//���S�t���O��getter
	const bool	 GetIsAttack	()const { return isAttack;			}//�U���t���O��getter
	const bool   GetIsHit		()const { return isHit;				}//�U���q�b�g�t���O��getter
	const int	 GetModelHandle	()const { return modelHandle;		}//���f���n���h����getter
	const void SetIsHit(const bool _isHitPlayer);
protected:
	enum class RandomSign
	{
		PLUS,//�{
		MINUS,//�[
	};
	/*�ÓI�萔*/
	static constexpr int RANDOM_RANGE = 7;//�����_���Ő�������l�͈̔�
	static const VECTOR  DESTROY_POS;			//HP���O�ɂȂ����Ƃ����̍��W�ɍs��
	/*�����o�ϐ�*/
	BloodParticle*	 blood;			//�����Ԃ��p�[�e�B�N��
	CharacterStatus* status;		//�X�e�[�^�X
	StrongerUI*		 strongerUI;	//���G�}�[�N
	SpawnParticle*	 spawnParticle;	//�X�|�[���p�[�e�B�N��

	VECTOR	spawnPos;				//�X�|�[���ʒu
	VECTOR	bloodBaseDir;			//�����Ԃ��p�[�e�B�N�����΂������̂��ƂɂȂ����
	float	maxHP;					//�ő�̗�
	int		frameCount;				//�t���[���J�E���g
	bool	isFarmBossEnemyPos;		//�t�@�[�����{�X���W���Z�b�g���邩�ǂ���
	bool	isAttackReadying;		//�U������
	int		waitAttackFrameCount;	//�U���ҋ@�t���[���J�E���g��
	int		spawnFrameCount;		//�X�|�[�����Ă���̃t���[����
	bool	isSpawn;				//�X�|�[��������
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
	bool isPrevColorChange;	//�O�ɐF��ύX������
	bool isChangeColor;		//�F�̕ύX�����Ă��邩�ǂ���
	int materialNum;		//�}�e���A���̐�
	Timer* changeColorTimer;//�F�ύX�^�C�}�[
	std::vector<COLOR_F> difColorInfo;//�f�B�t���[�Y�J���[���
	std::vector<COLOR_F> spcColorInfo;//�X�y�L�����J���[���
	std::vector<COLOR_F> emiColorInfo;//�G�~�b�V�u�J���[���
	std::vector<COLOR_F> ambColorInfo;//�A���r�G���g�J���[���
};

