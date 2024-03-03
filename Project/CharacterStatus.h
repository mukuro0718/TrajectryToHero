//===========================================================================
//@brief �X�e�[�^�X�N���X
// �L�����N�^�[���Ƃ̃X�e�[�^�X�̏�����
// �X�e�[�^�X�㏸�v�Z�������Ȃ�
//===========================================================================

#pragma once
#include"DxLib.h"
#include<vector>
#include<string>

using namespace std;
class Timer;
class CrackerParticle;
class CharacterStatus final
{
public:
    CharacterStatus();           //�R���X�g���N�^
    ~CharacterStatus();          //�f�X�g���N�^

    void Init();											// ������
    void Delete();											// �摜�n���h���A�N���X�C���X�^���X�̍폜
    void Update(const bool _isShowMenu);	// �X�V
    void Draw();								// �`��

    void InitTutorialStatus(const int _showCount);
    void InitWeakEnemyStatus(const float _playerLv);    //�X�e�[�^�X�̏����ݒ�
    void InitStrongEnemyStatus(const float _playerLv);  //�X�e�[�^�X�̏����ݒ�
    void InitBossEnemyStatus();                         //�X�e�[�^�X�̏����ݒ�
    void InitPlayerStatus();                            //�X�e�[�^�X�̏����ݒ�
    void InitExpToGive();                               //�o���l�̏�����
    void PhysicalRecovery();//�̗͉�
    float CalcHP(const float _atk);//HP�v�Z
    void CalcExp(const float _expToGive);//���x���A�b�v����
    const float GetAgi()const { return agi; }
    const float GetHp()const { return hp; }
    const float GetDef()const { return def; }
    const float GetLv()const { return lv; }
    const float GetAtk()const { return atk; }
    const int GetAtkUpCount()const { return atkUpCount; }
    const int GetAgiUpCount()const { return agiUpCount; }
    const int GetDefUpCount()const { return defUpCount; }
    const float GetMaxHP()const { return maxHp;}
    const float GetExp()const { return exp; }
    const float GetNeedExp()const { return needExp; }
    const bool GetIsShowMenu()const { return isShowMenu; }
    const bool GetIsBonfireMenu()const { return isBonfireMenu; }
    void ShowInfo();//���̕\��
    void TutorialStatusReset();
private:
    /*�N���X�E�\����*/
    enum class DataType
    {
        BACK_GROUND,
        BONFIRE_MENU,
        CURSOR,
        SELECT_RECT,
        ATK,
        AGI,
        DEF,
        A_BUTTON,
        B_BUTTON,
    };
    std::vector<int> data;
    //==============================
    //������΃��j���[
    //==============================
    enum class SelectBonfireMenu
    {
        BACK_TO_THE_GAME,//�Q�[���ɖ߂�
        LEVEL_UP,//���x���A�b�v
        BACK_TO_THE_TITLE,//�^�C�g���ɖ߂�
    };
    struct Vec2d
    {
        int x = 0;
        int y = 0;
    };
    static constexpr Vec2d menuPos = { 100,100 };
    static constexpr Vec2d highCursorPos = { 159,152 };
    static constexpr Vec2d lowCursorPos = { 175,967 };
    static constexpr int ADD_RECTPOS_VALUE = 64;
    static constexpr int FRAME_LIMIT = 60;
    static constexpr int RECTPOS_MIN_VALUE = 200;
    static constexpr int RECTPOS_MAX_VALUE = 792;

    static constexpr Vec2d GAME_POS = { 200,200 };
    static constexpr Vec2d LEVEL_POS = { 200,269 };
    static constexpr Vec2d TITLE_POS = { 200,338 };

    void UpdateBonfireMenu();
    void DrawBonfireMenu();

    Vec2d rectPos;
    int nowSelectMenu;
    int menuImage;
    int cursorImage;
    int rectImage;
    int frameCount;
    bool isInputPad;
    bool isFinalSelectMenu;
    bool isShowMenu;
    //=======================================
    //���x���A�b�v���j���[
    //=======================================
    enum class SelectStatus
    {
        ATK,
        AGI,
        DEF
    };
    struct DrawRect
    {
        int lx = 0;
        int ly = 0;
        int rx = 0;
        int ry = 0;
    };
    static constexpr DrawRect ATK_POS = { 600,450,800,650 };
    static constexpr DrawRect AGI_POS = { 900,450,1100,650 };
    static constexpr DrawRect DEF_POS = { 1200,450,1400,650 };
    static constexpr Vec2d ATK_TEXT_POS = { 650,420 };
    static constexpr Vec2d AGI_TEXT_POS = { 950,420 };
    static constexpr Vec2d DEF_TEXT_POS = { 1250,420 };
    static constexpr Vec2d TEXT_POS = { 600,300 };
    static constexpr Vec2d ATK_UP_COUNT_POS = { 670,700 };
    static constexpr Vec2d AGI_UP_COUNT_POS = { 960,700 };
    static constexpr Vec2d DEF_UP_COUNT_POS = { 1270,700 };

    static constexpr DrawRect ATK_HIGH_CURSOR_POS = { 670,670,700,700 };
    static constexpr DrawRect AGI_HIGH_CURSOR_POS = { 960,670,990,700 };
    static constexpr DrawRect DEF_HIGH_CURSOR_POS = { 1270,670,1300,700 };

    static constexpr DrawRect ATK_LOW_CURSOR_POS = { 670,760,700,730 };
    static constexpr DrawRect AGI_LOW_CURSOR_POS = { 960,760,990,730 };
    static constexpr DrawRect DEF_LOW_CURSOR_POS = { 1270,760,1300,730 };
    static constexpr DrawRect BACKGROUND_POS = {550,250,1450,800};

    static constexpr int MAX_ATK_UP_COUNT = 5;
    static constexpr int MAX_AGI_UP_COUNT = 5;
    static constexpr int MAX_DEF_UP_COUNT = 5;
    static constexpr float MAX_LV = 16.0f;

    static const int FONT_COLOR;
    static const int BLUE_FONT_COLOR;
    static const int PREV_FONT_COLOR;
    int atkImage;
    int agiImage;
    int defImage;
    int atkUpCount;
    int agiUpCount;
    int defUpCount;
    int prevAtkUpCount;
    int prevAgiUpCount;
    int prevDefUpCount;
    int nowSelectStatus;
    int statusUpPoint;
    int prevStatusUpPoint;
    DrawRect nowHighCursorPos;
    DrawRect nowLowCursorPos;
    void UpdateLevelUpMenu();
    void DrawLevelUpMenu();

    bool isBonfireMenu;
    bool isLevelUp;



    /*�ÓI�萔*/
    static constexpr float MIN_EXP = 5.0f;  //�^����Œ���̌o���l

    static constexpr float	IMG_SIZE = 5.0f;			//�摜�T�C�Y
    static constexpr float	IMG_ANGLE = 0.0f;			//��]��
    static constexpr float	LV_UP_ADD_VALUE = 1.0f;			//���x���A�b�v���X�e�[�^�X������
    static constexpr int	MODIFIABLE_STATUS_COUNT = 3;				//�ύX�\�ȃX�e�[�^�X�̐�
    static constexpr int	FONT_SIZE = 128;				//�t�H���g�̃T�C�Y
    static constexpr int	FONT_THICK = 64;				//�t�H���g�̑���
    static constexpr int	BACKGROUND_WIDTH = 900;				//�w�i�摜�̉�
    static constexpr int	BACKGROUND_HEIGHT = 980;				//�w�i�摜�̏c
    static const	 int	FONT_COLOR_RED;								//�t�H���g�̐F
    static const	 int	FONT_COLOR_WHITE;							//�t�H���g�̐F
    static const	 VECTOR SET_DRAW_POS;								//�`����W
    static constexpr Vec2d	STATUS_UP_TEXT_POS = { 650,100 };		//�X�e�[�^�X�A�b�v�e�L�X�g���W
    static constexpr Vec2d  STATUS_UP_COUNT_TEXT_POS[MODIFIABLE_STATUS_COUNT] =
    {
        {850,300},
        {850,500},
        {850,700},
    };
    static constexpr Vec2d	STATUS_TEXT_POS[MODIFIABLE_STATUS_COUNT] =	//�{�^�����W
    {
        {850,300},
        {850,500},
        {850,700},
    };
    static const VECTOR BONFIRE_POS;
    /*���������֐�*/
    void ChangeBlendRateDrawText(const int nowSelectStatus, const int statusType);//�u�����h����ς��ĕ`��
    /*�����o�ϐ�*/
    float  lv;          //���x��
    float  hp;          //�̗�
    float  atk;         //�U����
    float  def;         //�h���
    float  agi;         //�f����
    float  expToGive;   //�^����o���l
    float  exp;         //�o���l
    float  needExp;     //�K�v�o���l
    float  maxHp;       //�ő�HP
    float  prevLv;		//�O��̃��x��

    bool   isShowBonfireMenu;			//���j���[��\�����Ă��邩
    bool   isShowLevelUpMenu;			//���j���[��\�����Ă��邩
    bool   isLvUP;				//���x���A�b�v������
    bool   isFinalSelectStatus;	//�ŏI�I�ɑI�������X�e�[�^�X
    int    lvUpCount;			//���݂̃��x���A�b�v���i���̃��x������O�̃��x���������j
    int	   backGroundImage;		//�w�i�摜�n���h��
    Timer* inputWaitTimer;		//���͑ҋ@����
    int	   statusFontHandle;	//LvUp�����j���[�p�t�H���g�n���h��
    CrackerParticle* particle;

};