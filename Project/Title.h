//===========================================================================
//@brief �^�C�g���N���X
//===========================================================================
#pragma once
#include"DxLib.h"
#include<vector>
#include"Common.h"
using namespace std;

class TutorialStage;
class Camera;
class SwordGirl;
class OperationUI;
class TutorialEnemy;
class Collision;
class StatusUpParticle;

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
	struct Vec2d//2�����x�N�g���\����
	{
		int x = 0;
		int y = 0;
	};
	struct DrawRect//�`��͈͍\����
	{
		int lx = 0;
		int ly = 0;
		int rx = 0;
		int ry = 0;
	};
	enum class TitleData//�摜�^�C�v
	{
		LOGO,
		BACKGROUND,
		A_BUTTON,
		B_BUTTON,
		X_BUTTON,
		R_STICK,
		L_STICK,
		BOSS_UI,
	};
	enum class FontType
	{
		PLAYER,
		LOGO,
		TEXT,
		TEXT_2,
	};
	enum class PlayerData//�摜�^�C�v
	{
		MODEL,
		HP,
		EXP,
		FRAME,
	};
	enum class EnemyData//�摜�^�C�v
	{
		MODEL,
		UI,
	};
	enum class StageData//�摜�^�C�v
	{
		GROUND,
		GATE,
		PORTAL,
		SKYDOME,
		CAMPFIRE,
		FLAME,
	};
	static constexpr int TITLE_DATA_NUM = 2;		//�^�C�g�����S
	static constexpr int TITLE_FONT_DATA_NUM = 3;	//�t�H���g
	static constexpr int TITLE_PLAYER_DATA_NUM = 4;	//�v���C���[
	static constexpr int TITLE_ENEMY_DATA_NUM = 2;	//�G�l�~�[
	static constexpr int TITLE_STAGE_DATA_NUM = 6;	//�X�e�[�W
	static constexpr DrawRect TITLE_LOGO_POS = { 200, 200, 1720, 700 };
	static constexpr Vec2d START_ICON_POS = { 700 ,800 };//�X�^�[�g�A�C�R�����W
	static constexpr int MAX_ALPHA_VALUE = 255;//�ő�A���t�@�l
	static constexpr int MIN_ALPHA_VALUE = 0;//�ŏ��A���t�@�l
	static constexpr int ADD_ALPHA_VALUE = 5;//�A���t�@�l������
	static constexpr int INIT_FRAME_COUNT = 0;//�������p�t���[����
	static constexpr int MAX_FRAME_COUNT = 60;//�ő�t���[����
	static constexpr Vec2d TUTORIAL_LOGO_POS = { 300, 400};//�`���[�g���A�����S�`����W
	static constexpr DrawRect TUTORIAL_LOGO_LINE_POS = { 250, 610, 1720, 610 };//�`���[�g���A�����S�`����W
	static const int FONT_COLOR;//�t�H���g�̐F
	/*�����o�ϐ�*/
	vector<int> titleData;	//�摜�n���h��
	vector<int> fontData;
	vector<int> playerData;
	vector<int> enemyData;
	vector<int> stageData;
	int startIconAlpha;//�X�^�[�g�A�C�R���p�A���t�@
	int titleAlpha;//�^�C�g�����S�S�̂̕`��p�A���t�@
	int stageNameAlpha;//�`���[�g���A�����S�p�A���t�@
	int addAlphaValue;//�A���t�@�l������
	int frameCount;//�t���[����
	bool isChangeAddAlpha;//�A���t�@�l�����ʂ�ύX���邩
	bool isFrameCount;//�t���[�������J�E���g���邩
	bool isDrawTitleEnd;//�^�C�g�����S�̕`������S�ɏI�����邩�i�A���t�@�l���萔�ȉ��ɂȂ����痧�Ă�j
	bool isDrawTitleFinish;//�^�C�g���̕`����I�����邽�߂ɃA���t�@�l�̒l�����炷
	bool isDrawStageName;//�X�e�[�W����`�悷�邩
	bool isChangeScene;//�V�[����ύX����
	bool isTitleEnd;//�^�C�g�����I������i�Q�[�����I���j
	TutorialStage* stage;
	Camera* camera;
	SwordGirl* player;
	OperationUI* opeUI;
	TutorialEnemy* enemy;
	Collision* collision;
	StatusUpParticle* statusUpParticle;

	enum class TutorialProgress
	{
		MOVE,			//�ړ�
		CAMERA,			//�J��������
		ATTACK,			//�U��
		DESTROY_ENEMY_1,
		CAMPFIRE_2,		//���΂ɍs��
		STATUS_UP,
		DESTROY_ENEMY_2,//�G��|��
		GATE_2,
	};
	static constexpr int PROGRESS_NUM = 12;
	vector<bool> isProgress;
	/*���������֐�*/
	void ChangeTitleAlphaValue();//�^�C�g���̃A���t�@�l�̕ύX
	void DrawTitle();//�^�C�g���`��
	void DrawStageName();//�`���[�g���A���X�e�[�W�̕�����\������
	void DrawTutorialText();//�`���[�g���A��������`��
	void FragChanger();
	void FixMoveVec();
	void OnDamage();
	void DrawDetailedDescription();//�`���[�g���A���̏ڍׂȂ�`��
	bool isChange;
	int textAlpha;
	int tutorialProgress;
	bool isDrawText;
	int progressFrameCount;
	bool destroyEnemy;
	float prevPlayerAtk;
	static constexpr DrawRect BACKGROUND_POS_FOR_TEXT = { 500,200,1420,300 };
	static constexpr DrawRect BACKGROUND_POS_FOR_DESCRIPTION = { 1400,30,1910,520 };
	bool isDescription;
	static constexpr Vec2d TEXT_POS = { 620,230 };
	static constexpr Vec2d TEXT_POS_FOR_DESCRIPTION = { 1420,50 };
	static constexpr DrawRect BUTTON_POS = { 510,210,590,290 };
	static constexpr DrawRect BOSS_UI_DRAW_RECT = { 500,900,1420,1000 };//�ړ�UI�`��͈�
	int strongUI;
};
