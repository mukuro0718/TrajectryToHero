////===========================================================================
////@brief �X�e�[�^�X�Ǘ��N���X
//// �X�e�[�^�X�v�Z(�ύX)�A�X�e�[�^�X�摜�̕`��
////===========================================================================
//
//#pragma once
//
//#include"DxLib.h"
//#include<vector>
//#include<string>
//#include"CharacterStatus.h"
//
//using namespace std;
//class Timer;
//class StatusManager final
//{
//public:
//
//	StatusManager();										// �R���X�g���N�^
//	~StatusManager();										// �f�X�g���N�^
//	void CreateInstance();									// �쐬
//	void Init();											// ������
//	void Delete();											// �摜�n���h���A�N���X�C���X�^���X�̍폜
//	void Update(CharacterStatus* status);	// �X�V
//	void Draw();								// �`��
//	//���x���A�b�v��������getter/setter(�v���C���[���Őݒ�)
//	const bool GetIsLvUP()const { return isLvUP; }
//	void SetIsLvUP(const bool isLvUP) { this->isLvUP = isLvUP; }
//	//���j���[���J���Ă��邩
//	const bool GetIsShowMenu()const { return isShowMenu; }
//
//private:
//	//�N���X�E�\����
//	struct VEC2D
//	{
//		int x = 0;
//		int y = 0;
//	};
//	//�萔
//	enum class SelectStatus//�I�����Ă���X�e�[�^�X�̎��
//	{
//		ATK,//�U����
//		DEF,//�h���
//		AGI,//�f����
//	};
//	static constexpr float	IMG_SIZE				 = 5.0f;			//�摜�T�C�Y
//	static constexpr float	IMG_ANGLE				 = 0.0f;			//��]��
//	static constexpr float	LV_UP_ADD_VALUE			 = 1.0f;			//���x���A�b�v���X�e�[�^�X������
//	static constexpr int	MODIFIABLE_STATUS_COUNT  = 3;				//�ύX�\�ȃX�e�[�^�X�̐�
//	static constexpr int	FONT_SIZE				 = 128;				//�t�H���g�̃T�C�Y
//	static constexpr int	FONT_THICK				 = 64;				//�t�H���g�̑���
//	static constexpr int	BACKGROUND_WIDTH		 = 900;				//�w�i�摜�̉�
//	static constexpr int	BACKGROUND_HEIGHT		 = 980;				//�w�i�摜�̏c
//	static const	 int	FONT_COLOR_RED;								//�t�H���g�̐F
//	static const	 int	FONT_COLOR_WHITE;							//�t�H���g�̐F
//	static const	 VECTOR SET_DRAW_POS;								//�`����W
//	static constexpr VEC2D	BACKGROUND_POS			 = { 510,50 };		//���j���[�w�i���W
//	static constexpr VEC2D	STATUS_UP_TEXT_POS		 = { 650,100 };		//�X�e�[�^�X�A�b�v�e�L�X�g���W
//	static constexpr VEC2D	STATUS_TEXT_POS[MODIFIABLE_STATUS_COUNT] =	//�{�^�����W
//	{
//		{850,300},
//		{850,500},
//		{850,700},
//	};
//	//���������֐�
//	void ChangeSelectStatus();//�I�����Ă���X�e�[�^�X�̕ύX
//	void UpSelectStatus(CharacterStatus* status);//�I�����Ă���X�e�[�^�X�̏㏸
//	void ChangeBlendRateDrawText(const int nowSelectStatus, const int statusType);//�u�����h����ς��ĕ`��
//	//�ϐ�
//	float  prevLv;				//�O��̃��x��
//	bool   isShowMenu;			//���j���[��\�����Ă��邩
//	bool   isLvUP;				//���x���A�b�v������
//	bool   isFinalSelectStatus;	//�ŏI�I�ɑI�������X�e�[�^�X
//	bool   isInputPad;			//�X�e�B�b�N���͂��Ă��邩�i�A�����̖͂h�~�j
//	int    lvUpCount;			//���݂̃��x���A�b�v���i���̃��x������O�̃��x���������j
//	int    nowSelectStatus;		//���ݑI�����Ă���X�e�[�^�X
//	int	   backGroundImage;		//�w�i�摜�n���h��
//	Timer* inputWaitTimer;		//���͑ҋ@����
//	int	   statusFontHandle;	//LvUp�����j���[�p�t�H���g�n���h��
//};
//
//
