//===========================================================================
//@brief �v���C���[�N���X / �p��
// 
//===========================================================================
#pragma once

#include<DxLib.h>
#include<vector>
#include"PlayerBase.h"

class Animation;
class Timer;
class SwordGirl :public PlayerBase
{
public:
	SwordGirl(const int _modelHandle,const int _frameImage,const int _hpImage,const int _expImage, const int _font);	//��������R���X�g���N�^
	~SwordGirl();						//�f�X�g���N�^
	//��{����
	const void Update()override;	//�X�V
	const void Init()override;		//������

	const void Move(const VECTOR _cameraToPlayer);		//�ړ�����
	const void Attack();								//�U������
	const void Death();									//���S����
	const void AnimChange();							//�A�j���[�V�����̕ύX
	const void UpdateUI();								//UI�̍X�V
	const void DrawUI();								//UI�̕`��
	const void ChangeColor();							//�F�̕ύX
	const void ReSpawn();								//���X�|�[��
	const void PhysicalRecovery();						//�̗͉�
	const void DrawMenu();								//�X�e�[�^�X���j���[�̕\��
	const void StatusUpdate(const VECTOR _bonfirePos);	//�X�e�[�^�X�̍X�V
	const void FixMoveVec(const VECTOR _fixVec);		//�ړ��C��
	const void KnockBack();								//�̂�����
	//�m�b�N�o�b�N�̊J�n
	const void CountInvincibleTimer();					//���G���Ԃ̌v��
	/*getter/setter*/
	const void	 SetIsInvincible	()		{ isInvincible = false; }
	const VECTOR GetPos				()const { return pos;		}//���W��getter
	const void   InitPos			()		{ pos = ORIGIN_POS; }//���W�̏�����
	const bool	 GetIsAttack		()const { return isAttack;  }//�U���t���O��getter
	const bool   GetIsMove			()const { return isMove;	}//�ړ��t���O��getter
	const bool   GetIsHit			()const {return isHit; }	 //�U���q�b�g�t���O��getter
	const bool   GetIsBonfireMenu	()const;	//�X�e�[�^�X�N���X�̕��΃��j���[�\���t���O��getter
	const bool   GetIsShowStatusMenu();			//�X�e�[�^�X�N���X��isShowMenu��getter
	const int	 GetAtkUpCount		()const;	//�X�e�[�^�X�N���X�̕��΃��j���[�\���t���O��getter
	const int	 GetAgiUpCount		()const;	//�X�e�[�^�X�N���X�̕��΃��j���[�\���t���O��getter
	const int	 GetDefUpCount		()const;	//�X�e�[�^�X�N���X�̕��΃��j���[�\���t���O��getter
	const void	 OnKnockBack(const VECTOR _targetPos);
private:
	/*�\���́E�񋓑�*/
	struct CollisionSetUpInfo//�R���W�����\�z�p���
	{
		int frameIndex = 0;	//�R���W���������\�z�������t���[���̔ԍ�
		int xDivNum = 0;	//X�R���W����������
		int yDivNum = 0;	//y�R���W����������
		int zDivNum = 0;	//z�R���W����������
	};
	struct RangeOfAction//�s���\�͈�
	{
		float LX = 0;
		float LZ = 0;
		float RX = 0;
		float RZ = 0;
	};
	enum class AnimationType//�A�j���[�V�����̎��
	{
		RUN,        //����A�j���[�V����
		ATTACK,		//�U���A�j���[�V����
		FRIGHTENING,//���݃A�j���[�V����
		AVOIDANCE,	//����A�j���[�V����
		IDLE,       //�ҋ@�A�j���[�V����
		DEATH,      //���S�A�j���[�V����
	};
	enum class ComboType
	{
		NONE,
		ONE,
		TWO,
		FINISH,
	};
	/*�ÓI�萔*/
	static constexpr RangeOfAction		HP_FRAME_POS				 = { 90,60,390,90 }		;//HP�t���[�����W
	static constexpr RangeOfAction		EXP_FRAME_POS				 = { 90,100,390,130 }	;//EXP�t���[�����W
	static constexpr CollisionSetUpInfo PLAYER_COLL_INFO			 = { 66,1,1,1 }			;//�v���C���[�R���W�������
	static constexpr RangeOfAction		PLAYER_RANGE_OF_ACTION		 = { 451,510, -450,-840};//�v���C���[�s���\�͈�
	static constexpr InputAnalogStick	NONE_INPUT_VALUE			 = { 0,0 }				;//�X�e�B�b�N���͂��Ȃ�
	static constexpr VEC2D				HP_BAR_POS					 = { 90,60 }			;//HP�t���[�����W
	static constexpr VEC2D				EXP_BAR_POS					 = { 90,100, }			;//EXP�t���[�����W
	static constexpr float				ANGLE_VALUE					 = 30.0f				;//�p�x�̑�����
	static constexpr float				PLAYER_RADIUS				 = 8.0f					;//���G����
	static constexpr float				PLAYETR_Y_POS				 = 10.0f				;//�v���C���[Y���W
	static constexpr float				LV_MULT_VALUE				 = 10.0f				;//���x���{��
	static constexpr float				FIRST_ANIM_PLAY_TIME		 = 0.0f					;//�A�j���[�V���������Đ�����
	static constexpr int				STAY_TIMER_TARGET_TIME		 = 3000					;//�ҋ@����
	static constexpr int				INVINCIBLE_TIMER_TARGET_TIME = 2					;//���G����
	static constexpr int				TOTAL_ANIM_NUM				 = 6					;//�A�j���[�V������
	static const VECTOR  FIRST_MODEL_SCALE;	//���f���̏����g�嗦
	static const VECTOR  FIRST_MODEL_ROTATE;//���f���̏�����]�l
	static const VECTOR  FIRST_POS;			//�v���C���[���������W
	static const COLOR_F CHANGE_DIF_COLOR;	//�f�B�t���[�Y�J���[
	static const COLOR_F CHANGE_SPC_COLOR;	//�X�y�L�����J���[
	static const COLOR_F CHANGE_EMI_COLOR;	//�G�~�b�V�u�J���[
	static const COLOR_F CHANGE_AMB_COLOR;	//�A���r�G���g�J���[
	static const int	 FONT_COLOR;		//�t�H���g�J���[
	
	/*���������֐�*/
	void Create();	//����
	
	/*�����o�ϐ�*/
	Animation*		 anim;				//�A�j���[�V�����N���X
	Timer*			 stayTimer;			//�҂����ԃN���X
	Timer*			 invincibleTimer;	//���G����

	std::vector<COLOR_F> difColorInfo;	//�f�B�t���[�Y�J���[���
	std::vector<COLOR_F> spcColorInfo;	//�X�y�L�����J���[���
	std::vector<COLOR_F> emiColorInfo;	//�G�~�b�V�u�J���[���
	std::vector<COLOR_F> ambColorInfo;	//�A���r�G���g�J���[���
	
	InputAnalogStick inputLeftStick;	//���X�e�B�b�N���͍\����
	VECTOR playerDir;					//�v���C���[�̌����Ă�������i�ړ������Ƃ��̂ݕۑ��j
	VECTOR prevPos;						//�O��̍��W
	VECTOR knockBackMoveVec;			//�ړ��x�N�g���̋t�s��
	VEC2D nowHP;						//���݂̗̑�
	VEC2D prevHP;						//�O��̗̑�
	VEC2D nowEXP;						//���݂̌o���l
	float multSpeed;					//�X�s�[�h�ɂ�����l
	float avoidSpeed;					//��𒆂̃X�s�[�h
	float animPlayTime[TOTAL_ANIM_NUM];	//�A�j���[�V�����Đ�����
	bool isMove;						//�ړ����Ă��邩�ǂ���
	bool isAvoidance;					//����t���O
	bool isKnockBack;					//�̂�����t���O
	bool isChangeColor;					//�F�̕ύX�����Ă��邩�ǂ���
	int materialNum;					//�}�e���A���̐�
	int font;							//�t�H���g�f�[�^
	int frameImage;						//�t���[���摜
	int hpImage;						//�̗͉摜
	int expImage;						//�o���l�摜
	int knockBackFrameCount;			//�m�b�N�o�b�N���̃t���[����
};
