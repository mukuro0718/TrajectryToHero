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

class CharacterStatus final
{
public:
    CharacterStatus();           //�R���X�g���N�^
    ~CharacterStatus();          //�f�X�g���N�^

    void Init();											// ������
    void Delete();											// �摜�n���h���A�N���X�C���X�^���X�̍폜
    void Update();	// �X�V
    void Draw();								// �`��


    void InitWeakEnemyStatus();      //�X�e�[�^�X�̏����ݒ�
    void InitStrongEnemyStatus();    //�X�e�[�^�X�̏����ݒ�
    void InitBossEnemyStatus();      //�X�e�[�^�X�̏����ݒ�
    void InitPlayerStatus();         //�X�e�[�^�X�̏����ݒ�

    float CalcHP(const float _atk);//HP�v�Z
    void CalcExp(const float _expToGive);//���x���A�b�v����
    void InitExpToGive();
    const float GetAgi()const { return agi; }
    const float GetHp()const { return hp; }
    const float GetLv()const { return lv; }
    const float GetAtk()const { return atk; }
    const bool GetIsShowMenu()const { return isShowMenu; }
    void ShowInfo();//���̕\��
private:
    /*�N���X�E�\����*/
    struct VEC2D
    {
        int x = 0;
        int y = 0;
    };
    enum class SelectStatus//�I�����Ă���X�e�[�^�X�̎��
    {
        ATK,//�U����
        DEF,//�h���
        AGI,//�f����
    };
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
    static constexpr VEC2D	BACKGROUND_POS = { 510,50 };		//���j���[�w�i���W
    static constexpr VEC2D	STATUS_UP_TEXT_POS = { 650,100 };		//�X�e�[�^�X�A�b�v�e�L�X�g���W
    static constexpr VEC2D	STATUS_TEXT_POS[MODIFIABLE_STATUS_COUNT] =	//�{�^�����W
    {
        {850,300},
        {850,500},
        {850,700},
    };

    /*���������֐�*/
    void ChangeSelectStatus();//�I�����Ă���X�e�[�^�X�̕ύX
    void UpSelectStatus();//�I�����Ă���X�e�[�^�X�̏㏸
    void ChangeBlendRateDrawText(const int nowSelectStatus, const int statusType);//�u�����h����ς��ĕ`��

    /*�����o�ϐ�*/
    float  lv;        //���x��
    float  hp;          //�̗�
    float  atk;          //�U����
    float  def;         //�h���
    float  agi;         //�f����
    float  expToGive;          //�^����o���l
    float  exp;          //�o���l
    float  needExp;          //�K�v�o���l
    float  maxHp;          //�ő�HP

    float  prevLv;				//�O��̃��x��
    bool   isShowMenu;			//���j���[��\�����Ă��邩
    bool   isLvUP;				//���x���A�b�v������
    bool   isFinalSelectStatus;	//�ŏI�I�ɑI�������X�e�[�^�X
    bool   isInputPad;			//�X�e�B�b�N���͂��Ă��邩�i�A�����̖͂h�~�j
    int    lvUpCount;			//���݂̃��x���A�b�v���i���̃��x������O�̃��x���������j
    int    nowSelectStatus;		//���ݑI�����Ă���X�e�[�^�X
    int	   backGroundImage;		//�w�i�摜�n���h��
    Timer* inputWaitTimer;		//���͑ҋ@����
    int	   statusFontHandle;	//LvUp�����j���[�p�t�H���g�n���h��

};