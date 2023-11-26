//===========================================================================
//@brief �^�C�g���N���X
//===========================================================================
#pragma once
#include"DxLib.h"
#include<vector>
#include"Common.h"
using namespace std;
class Title final
{
public:
	Title();	//�R���X�g���N�^
	~Title();	//�f�X�g���N�^

	void Init();	//������
	void Update();	//�X�V
	void Draw();	//�`��
	
	//�^�C�g���I���t���O��getter
	const bool GetIsTitleEnd()const { return isTitleEnd; }
	//�V�[���ύX�t���O��getter
	const bool GetIsChangeScene()const { return isChangeScene; }
private:
	/*�萔*/
	enum class CursorType//�J�[�\���^�C�v
	{
		ESCAPE,		//�����A�C�R��
		GO,			//�i�ރA�C�R��
		BRIEFING,	//�󋵐����A�C�R��
	};
	enum class ImageType//�摜�^�C�v
	{
		ESCAPE_ICON,	//�����A�C�R��
		GO_ICON,		//�i�ރA�C�R��
		BRIEFING_ICON,	//�����A�C�R��
		TITLE_TEXT,		//�^�C�g������
		CURSOR,			//�J�[�\��
		BACKGROUND,		//�w�i
		BRIEFING_DATA,	//�������e
		MOVE_BACKGROUND1,//�w�i�摜
		MOVE_BACKGROUND2,
		MOVE_BACKGROUND3,
		MOVE_BACKGROUND4,
		MOVE_BACKGROUND5,
		MOVE_BACKGROUND6,
		MOVE_BACKGROUND7,
	};
	enum class MoveBackGround//�w�i�摜
	{
		MOVE_BACKGROUND1,
		MOVE_BACKGROUND2,
		MOVE_BACKGROUND3,
		MOVE_BACKGROUND4,
		MOVE_BACKGROUND5,
		MOVE_BACKGROUND6,
		MOVE_BACKGROUND7,
	};
	/*�ÓI�萔*/
	static constexpr VEC2D	INIT_ESCAPE_ICON_POS						= { 148 ,880 }	 ;	//�����A�C�R�����������W
	static constexpr VEC2D	INIT_GO_ICON_POS							= { 795 ,880 }	 ;	//�Q�[���X�^�[�g�A�C�R�����������W
	static constexpr VEC2D	INIT_BRIEFING_ICON_POS						= { 1129,880 }	 ;	//�����A�C�R�����������W
	static constexpr VEC2D	INIT_BRIEFING_DATA_POS						= { 500 ,-50 }	 ;	//�������e�摜���W
	static constexpr VEC2D	INIT_TITLE_POS								= { 349 ,46	 }	 ;	//�^�C�g���������������W
	static constexpr VEC2D	INIT_CURSOR_POS_OF_ESCAPE					= { 398 ,880 }	 ;	//�����A�C�R�����������W
	static constexpr VEC2D	INIT_CURSOR_POS_OF_GO						= { 860 ,880 }	 ;	//�Q�[���X�^�[�g�A�C�R�����������W
	static constexpr VEC2D	INIT_CURSOR_POS_OF_BRIEFING					= { 1450,880 }	 ;	//�����A�C�R�����������W
	static constexpr VEC2D	ORIGIN_POS_2D								= { 0	,0	 }	 ;	//2D�x�N�g�����������W
	static constexpr int	ADD_ALPHA_VALUE								= 2				 ;	//�A���t�@������
	static constexpr int	MAX_ALPHA_VALUE								= 200			 ;	//�ő�A���t�@��
	static constexpr int	MIN_ALPHA_VALUE								= 0				 ;	//�ŏ��A���t�@��
	static constexpr int	MAX_WAIT_COUNT								= 10			 ;	 //�ő�ҋ@��
	static constexpr int	INIT_WAIT_COUNT								= 0				 ;	//�������ҋ@��
	static constexpr int	MAX_BACKGROUND_NUM							= 7				 ;	//�w�i�摜��
	static constexpr int	MOVE_BACKGROUND_SPEED[MAX_BACKGROUND_NUM]	= {1,2,3,4,5,6,7};	//�����w�i�̃X�s�[�h
	static constexpr int	MAX_BACKGROUND_POS							= 1920			 ;	//�����w�i�̍ő���W
	static constexpr int	INIT_X_POS									= 0				 ;	//������Y���W
	static constexpr int	INIT_Y_POS									= 0				 ;	//������Y���W
	static constexpr int	MAX_Y_POS									= 5				 ;	//�ő�Y���W
	static constexpr int	MIN_Y_POS									= -20			 ;	//�ŏ�Y���W
	static constexpr int	MAX_Y_VALUE									= 1				 ;	//Y���W������
	static constexpr int	MIN_Y_VALUE									= -1			 ;	//Y���W������
	/*���������֐�*/
	void ChangeCursor();		//�J�[�\�����W�̕ύX
	void DrawMoveBackGround();	//�����w�i�̕`��
	void FloatCursor();			//�J�[�\���̏㉺�ړ�����
	/*�����o�ϐ�*/
	vector<int> image;									//�摜�n���h��
	VEC2D		escapeIconPos;							//�����A�C�R�����W
	VEC2D		goIconPos;								//�Q�[���X�^�[�g�A�C�R�����W
	VEC2D		briefingIconPos;						//�����A�C�R�����W
	VEC2D		briefingDataImgPos;						//�������e�摜
	VEC2D		titlePos;								//�^�C�g���������W
	VEC2D		cursorPos;								//�J�[�\�����W
	VEC2D		moveBackGroundPos[MAX_BACKGROUND_NUM];	//�����w�i1�̍��W
	bool		isInputState;							//���͏�ԃt���O�i���͂���Ă���Ftrue����ȊO�Ffalse�j
	bool		isSelectIcon;							//�A�C�R����I�����Ă��邩�ǂ���
	bool		isShowBriefing;							//������\�����Ă��邩�ǂ���
	bool		isTitleEnd;								//�^�C�g���I���t���O
	bool		isChangeScene;							//�V�[���؂�ւ��t���O
	int			alpha;									//�A���t�@�l
	int			nowWaitCount;							//���݂̑ҋ@�J�E���g
	int			nowSelectIconType;						//�I�����Ă���A�C�R���̎�ށi0:escape 1:go 2:briefing�j
	int			floatY;									//Y���W
	int			floatYAddValue;							//Y���W������
};
