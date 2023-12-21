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
	SwordGirl(){};						//�R���X�g���N�^
	SwordGirl(const int _modelHandle,const int _frameImage,const int _hpImage,const int _expImage);	//��������R���X�g���N�^
	~SwordGirl();						//�f�X�g���N�^
	void Update()override;				//�X�V
	void Init()override;				//������
	void Move(const VECTOR cameraToPlayer);//�ړ�����
	void Attack();//�U������
	void Death();//���S����
	void AnimChange();//�A�j���[�V�����̕ύX
	void CountInvincibleTimer();//���G���Ԃ̌v��
	const VECTOR GetPos()const { return pos; }//���W��getter
	const bool GetIsAttack()const { return isAttack; }//�U���t���O��getter
	void DrawMenu();//�X�e�[�^�X���j���[�̕\��
	const bool GetIsShowStatusMenu();//�X�e�[�^�X�N���X��isShowMenu��Ԃ�
	void StatusUpdate();//�X�e�[�^�X�̍X�V
	void FixMoveVec(const VECTOR _fixVec);//�ړ��C��
	void UpdateUI();//UI�̍X�V
	void DrawUI();//UI�̕`��
	void ChangeColor();//�F�̕ύX
private:
	/*�萔*/
	enum class AnimationType//�A�j���[�V�����̎��
	{
		RUN,        //����A�j���[�V����
		ATTACK,		//�U���A�j���[�V����
		IDLE,       //�ҋ@�A�j���[�V����
		DEATH,      //���S�A�j���[�V����
	};
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
	static const	 VECTOR FIRST_MODEL_SCALE;	//���f���̏����g�嗦
	static const	 VECTOR FIRST_MODEL_ROTATE;	//���f���̏�����]�l
	static const	 VECTOR FIRST_POS;//�v���C���[���������W
	static const COLOR_F CHANGE_DIF_COLOR;//�f�B�t���[�Y�J���[
	static const COLOR_F CHANGE_SPC_COLOR;//�X�y�L�����J���[
	static const COLOR_F CHANGE_EMI_COLOR;//�G�~�b�V�u�J���[
	static const COLOR_F CHANGE_AMB_COLOR;//�A���r�G���g�J���[
	static constexpr VEC2D HP_FRAME_POS = { 0,0 };//HP�t���[�����W
	static constexpr VEC2D EXP_FRAME_POS = { 0,0 };//EXP�t���[�����W
	static constexpr CollisionSetUpInfo PLAYER_COLL_INFO			 = { 66,1,1,1 }			;//�v���C���[�R���W�������
	static constexpr RangeOfAction		PLAYER_RANGE_OF_ACTION		 = { 451,-450,510,-400 };//�v���C���[�s���\�͈�
	static constexpr InputAnalogStick	NONE_INPUT_VALUE			 = { 0,0 }				;//�X�e�B�b�N���͂��Ȃ�
	static constexpr int				STAY_TIMER_TARGET_TIME		 = 3000					;//�ҋ@����
	static constexpr int				INVINCIBLE_TIMER_TARGET_TIME = 2					;//���G����
	static constexpr float				ANGLE_VALUE					 = 30.0f				;//�p�x�̑�����
	static constexpr float				PLAYER_RADIUS				 = 8.0f					;//���G����
	static constexpr float				PLAYETR_Y_POS				 = 10.0f				;//�v���C���[Y���W
	static constexpr float				LV_MULT_VALUE				 = 10.0f				;//���x���{��
	static constexpr float				FIRST_ANIM_PLAY_TIME		 = 0.0f					;//�A�j���[�V���������Đ�����
	/*���������֐�*/
	void Create();	//����
	/*�����o�ϐ�*/
	Animation*		anim;			//�A�j���[�V�����N���X
	Timer*			stayTimer;		//�҂����ԃN���X
	Timer*			invincibleTimer;//���G����
	InputAnalogStick inputLeftStick;	//���X�e�B�b�N���͍\����
	int prevLv;
	bool isMove;//�ړ����Ă��邩�ǂ���
	bool isChangeColor;//�F�̕ύX�����Ă��邩�ǂ���
	int materialNum;//�}�e���A���̐�
	std::vector<COLOR_F> difColorInfo;//�f�B�t���[�Y�J���[���
	std::vector<COLOR_F> spcColorInfo;//�X�y�L�����J���[���
	std::vector<COLOR_F> emiColorInfo;//�G�~�b�V�u�J���[���
	std::vector<COLOR_F> ambColorInfo;//�A���r�G���g�J���[���
	int frameImage;
	int hpImage;
	int expImage;
};
