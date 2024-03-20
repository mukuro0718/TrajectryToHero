//===================================================
//@brief �`���[�g���A���G�l�~�[�N���X
// �`���[�g���A���ł̃G�l�~�[�̓�������������
//===================================================
#pragma once
#include<DxLib.h>
#include"Common.h"
#include<vector>


class WeakEnemy;
class CharacterStatus;
class Animation;
class Shadow;
class StrongerUI;
class BloodParticle;
class Timer;

class TutorialEnemy final
{
public:
	TutorialEnemy(const int _modelHandle);	//�R���X�g���N�^
	~TutorialEnemy();						//�f�X�g���N�^
	
	const void  Create(const int _bloodImage);											//�쐬�iInit�֐��ōs���Ȃ��������s���j
	const void  Init();												//������
	const void  Delete();											//�폜
	const void  Draw(const float _playerLv);						//�`��
	const void  Update();											//�X�V
	const void  DrawShadow(const int _stageModelHandle);			//�e�̕`��
	const void  InitExpToGive();									//�o���l�̏�����
	const void  OffIsDamage() { isDamage = false; }					//�_���[�W�t���O������
	const float CalcHP(const float _atk, const VECTOR _attackPos);	//HP�̌v�Z
	/*�e�t���O��getter/setter*/
	const bool GetIsDamage()	const { return isDamage; }
	const bool GetIsRespawn()	const { return isRespawn; }
	const bool GetIsDeath()		const { return isDeath; }
	const float GetRadius()		const { return RADIUS; }
	const VECTOR GetPos()		const { return pos; }
	const CapsuleInfo GetCapsuleInfo()const { return capsule; }

private:
	/*�\���́E�񋓑�*/
	enum class AnimationType
	{
		IDLE,
		DEATH,
	};
	/*�ÓI�萔*/
	static constexpr VECTOR  SCALE		= { 0.2f,0.2f,0.2f };						//�g�嗦
	static constexpr VECTOR  ROTATE		= { 0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f };//��]��
	static constexpr VECTOR  DESTROY_POS = { 500.0f, 500.0f, 500.0f };				//���S�����Ƃ��̍��W
	static constexpr VECTOR  INIT_POS	= { 0.0f,0.0f,-150.0f };					//���W�̏�����
	static constexpr float	 RADIUS		= 10.0f;									//���a
	static constexpr int	 MAX_FRAME_COUNT = 60;									//�ő�t���[����
	
	static const	 int	 CAPSULE_COLOR;		//�J�v�Z���̐F
	static const	 COLOR_F CHANGE_DIF_COLOR;	//�f�B�t���[�Y�J���[
	static const	 COLOR_F CHANGE_SPC_COLOR;	//�X�y�L�����J���[
	static const	 COLOR_F CHANGE_EMI_COLOR;	//�G�~�b�V�u�J���[
	static const	 COLOR_F CHANGE_AMB_COLOR;	//�A���r�G���g�J���[
	/*���������֐�*/
	const void SetUpCapsule();	//�J�v�Z�����̐ݒ�
	const void ChangeAnim();	//�A�j���[�V�����̕ύX
	const void ChangeColor();	//�F�̕ύX
	/*�����o�ϐ�*/
	CharacterStatus* status;		  //�X�e�[�^�X
	BloodParticle*	 blood;			  //�����Ԃ�
	StrongerUI*		 strongerUI;	  //���GUI
	Animation*		 anim;			  //�A�j���[�V����
	Shadow*			 shadow;		  //�e
	Timer*			 changeColorTimer;//�F�ύX�^�C�}�[
	
	std::vector<COLOR_F> difColorInfo;	//�f�B�t���[�Y�J���[���
	std::vector<COLOR_F> spcColorInfo;	//�X�y�L�����J���[���
	std::vector<COLOR_F> emiColorInfo;	//�G�~�b�V�u�J���[���
	std::vector<COLOR_F> ambColorInfo;	//�A���r�G���g�J���[���

	CapsuleInfo capsule;	//�J�v�Z�����
	VECTOR pos;				//���W
	VECTOR bloodBaseDir;	//�����Ԃ��p�[�e�B�N�����΂������̂��ƂɂȂ����
	bool isDeath;			//���S�t���O
	bool isInvincible;		//���G�t���O
	bool isDamage;			//�_���[�W�t���O
	bool isRespawn;			//���X�|�[���t���O
	bool isPrevColorChange;	//�O�̃t���[���ŐF��ύX���Ă�����
	bool isChangeColor;		//�F�̕ύX�����Ă��邩�ǂ���
	int frameCount;			//�o�߂����t���[��
	int modelHandle;		//���f���̃n���h��
	int initCount;			//���񏉊���������
	int materialNum;		//�}�e���A���̐�
	int animModel;			//�A�j���[�V�����p���f��
};

