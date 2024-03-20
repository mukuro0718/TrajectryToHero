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

    const void Init();											// ������
    const void Delete();											// �摜�n���h���A�N���X�C���X�^���X�̍폜
    const void Update(const bool _isShowMenu);	// �X�V
    const void Draw();								// �`��

    const void  InitTutorialStatus(const int _showCount);
    const void  InitWeakEnemyStatus(const float _playerLv);    //�X�e�[�^�X�̏����ݒ�
    const void  InitStrongEnemyStatus(const float _playerLv);  //�X�e�[�^�X�̏����ݒ�
    const void  InitBossEnemyStatus();                         //�X�e�[�^�X�̏����ݒ�
    const void  InitPlayerStatus();                            //�X�e�[�^�X�̏����ݒ�
    const void  InitExpToGive();                               //�o���l�̏�����
    const void  PhysicalRecovery();//�̗͉�
    const void  CalcExp(const float _expToGive);//���x���A�b�v����
    const void  ShowInfo();//���̕\��
    const void  TutorialStatusReset();
    const float CalcHP(const float _atk);//HP�v�Z

    /*getter*/
    const bool  GetIsShowMenu()const { return isShowMenu; }
    const bool  GetIsBonfireMenu()const { return isBonfireMenu; }
    const float GetAgi()const { return agi; }
    const float GetHp()const { return hp; }
    const float GetLv()const { return lv; }
    const float GetAtk()const { return atk; }
    const float GetMaxHP()const { return maxHp;}
    const float GetExp()const { return exp; }
    const float GetNeedExp()const { return needExp; }
    const int   GetAtkUpCount()const { return atkUpCount; }
    const int   GetAgiUpCount()const { return agiUpCount; }
    const int   GetDefUpCount()const { return defUpCount; }
private:
    /*�\���́E�񋓑�*/
    enum class DataType//���[�h�����f�[�^�̎��
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
    enum class SelectBonfireMenu//������΃��j���[
    {
        BACK_TO_THE_GAME,//�Q�[���ɖ߂�
        LEVEL_UP,//���x���A�b�v
        BACK_TO_THE_TITLE,//�^�C�g���ɖ߂�
    };
    struct Vec2d//2D�x�N�g���\����
    {
        int x = 0;
        int y = 0;
    };
    enum class SelectStatus//�X�e�[�^�X���
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
    /*�ÓI�萔*/
    static constexpr DrawRect ATK_POS             = { 600,450,800,650 };    //�U���摜�`��͈�
    static constexpr DrawRect AGI_POS             = { 900,450,1100,650 };   //�f�����摜�`��͈�
    static constexpr DrawRect DEF_POS             = { 1200,450,1400,650 };  //�h��͉摜�`��͈�
    static constexpr DrawRect ATK_HIGH_CURSOR_POS = { 670,670,700,700 };    //������W
    static constexpr DrawRect AGI_HIGH_CURSOR_POS = { 960,670,990,700 };    //������W
    static constexpr DrawRect DEF_HIGH_CURSOR_POS = { 1270,670,1300,700 };  //������W
    static constexpr DrawRect ATK_LOW_CURSOR_POS  = { 670,760,700,730 };    //�������W
    static constexpr DrawRect AGI_LOW_CURSOR_POS  = { 960,760,990,730 };    //�������W
    static constexpr DrawRect DEF_LOW_CURSOR_POS  = { 1270,760,1300,730 };  //�������W
    static constexpr DrawRect BACKGROUND_POS      = {550,250,1450,800};     //�w�i�`��ʒu
    static constexpr Vec2d    menuPos             = { 100,100 };            //���j���[���W
    static constexpr Vec2d    highCursorPos       = { 159,152 };            //������W
    static constexpr Vec2d    lowCursorPos        = { 175,967 };            //�������W
    static constexpr Vec2d    GAME_POS            = { 200,200 };            //�I���ʒu�i�Q�[���ɖ߂�j
    static constexpr Vec2d    LEVEL_POS           = { 200,269 };            //�I���ʒu�i���x���A�b�v�j
    static constexpr Vec2d    ATK_TEXT_POS        = { 650,420 };            //�����`��ʒu
    static constexpr Vec2d    AGI_TEXT_POS        = { 950,420 };            //�����`��ʒu
    static constexpr Vec2d    DEF_TEXT_POS        = { 1250,420 };           //�����`��ʒu
    static constexpr Vec2d    TEXT_POS            = { 600,300 };            //���x���A�b�v���j���[�^�C�g�������`��ʒu
    static constexpr Vec2d    ATK_UP_COUNT_POS    = { 670,700 };            //�U���͏㏸�񐔕`��ʒu
    static constexpr Vec2d    AGI_UP_COUNT_POS    = { 960,700 };            //�f�����㏸�񐔕`��ʒu
    static constexpr Vec2d    DEF_UP_COUNT_POS    = { 1270,700 };           //�h��͏㏸�񐔕`��ʒu
    static constexpr float    MAX_LV              = 16.0f;                  //�ő僌�x��
    static constexpr int      MAX_ATK_UP_COUNT    = 5;                      //�ő�X�e�[�^�X�㏸��
    static constexpr int      MAX_AGI_UP_COUNT    = 5;                      //�ő�X�e�[�^�X�㏸��
    static constexpr int      MAX_DEF_UP_COUNT    = 5;                      //�ő�X�e�[�^�X�㏸��

    static const int FONT_COLOR;//�����̐F
    static const int BLUE_FONT_COLOR;//�����i�F�j

    /*���������֐�*/
    const void UpdateBonfireMenu();
    const void DrawBonfireMenu();
    const void UpdateLevelUpMenu();
    const void DrawLevelUpMenu();

    /*�����o�ϐ�*/
    CrackerParticle* particle;          //�X�e�[�^�X�A�b�v���p�[�e�B�N��
    Timer*           inputWaitTimer;	//���͑ҋ@����

    DrawRect nowHighCursorPos;  //���݂̏���`��ʒu
    DrawRect nowLowCursorPos;   //���݂̉����`��ʒu
    Vec2d    rectPos;           //�I���ʒu�i�킩��₷���悤�ɕ`�悷��摜�̈ʒu�j
    float    lv;                //���x��
    float    hp;                //�̗�
    float    atk;               //�U����
    float    def;               //�h���
    float    agi;               //�f����
    float    expToGive;         //�^����o���l
    float    exp;               //�o���l
    float    needExp;           //�K�v�o���l
    float    maxHp;             //�ő�HP
    float    prevLv;		    //�O��̃��x��
    bool     isInputPad;        //���͂���������
    bool     isFinalSelectMenu; //���j���[��ł̍ŏI����iA�{�^���������ꂽ���j
    bool     isShowMenu;        //���j���[��\�����Ă��邩
    bool     isLevelUp;         //���x���A�b�v���Ă��邩
    bool     isBonfireMenu;     //���΃��j���[��\�����Ă��邩
    bool     isShowLevelUpMenu;	//���j���[��\�����Ă��邩
    int      nowSelectMenu;     //���ݑI�����Ă��郁�j���[
    int      atkUpCount;        //�X�e�[�^�X�㏸��
    int      agiUpCount;        //�X�e�[�^�X�㏸��
    int      defUpCount;        //�X�e�[�^�X�㏸��
    int      prevAtkUpCount;    //�ȑO�̃X�e�[�^�X�㏸��
    int      prevAgiUpCount;    //�ȑO�̃X�e�[�^�X�㏸��
    int      prevDefUpCount;    //�ȑO�̃X�e�[�^�X�㏸��
    int      nowSelectStatus;   //���ݑI�����Ă���X�e�[�^�X
    int      statusUpPoint;     //�X�e�[�^�X�㏸�|�C���g
    int      prevStatusUpPoint; //�ȑO�̃X�e�[�^�X�㏸�|�C���g

    std::vector<int> data;//���[�h�����f�[�^
};