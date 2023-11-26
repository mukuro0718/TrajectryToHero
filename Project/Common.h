//===========================================================================
//@brief ���ʃN���X
// �e�N���X�ŋ��ʂ��Ďg���萔��֐����`
//===========================================================================

#pragma once
#include"DxLib.h"

static constexpr int    WINDOW_WIDTH  = 1920;                   //�E�B���h�E���T�C�Y
static constexpr int    WINDOW_HEIGHT = 1080;                   //�E�B���h�E�c�T�C�Y
static constexpr int    COLOR_BIT     = 16;                     //�J���[�r�b�g
static const     VECTOR ORIGIN_POS    = VGet(0.0f, 0.0f, 0.0f); //�O���W


//�L�����N�^�[�̋��ʃX�e�[�^�X
struct CharacterStatus
{
    float  HP           = 0.0f;         //�̗�
    float  ATK          = 0.0f;         //�U����
    float  DEF          = 0.0f;         //�h���
    float  AGI          = 0.0f;         //�f����
    float  LV           = 0.0f;         //���x��
    float  EXP_TO_GIVE  = 0.0f;         //�^����o���l
    float  EXP          = 0.0f;         //�o���l
    bool   isHit        = false;		//����������
    bool   isInvincible = false;        //���G���
};
//�L�����N�^�[���ʃx�[�X
struct CharacterBase
{
    VECTOR pos         = ORIGIN_POS;    //���W
    VECTOR rotate      = ORIGIN_POS;    //��]��
    VECTOR scale       = ORIGIN_POS;    //�g�嗦
    float  radius      = 0.0f;          //���a
    int    modelHandle = 0;			    //���f���n���h��
    bool   isSelectAttack = false;      //�U����I�����Ă��邩
    bool   isAttack    = false;		    //�U������
    bool   isDeath     = false;			//���S�A�j���[�V������`�悵�I�������
    bool   isHit       = false;         //���a���q�b�g������
    VECTOR  correctionValue = ORIGIN_POS;      //�␳�l
};
struct VEC2D//�QD�x�N�g���\����
{
    int x = 0;
    int y = 0;
};
enum class SceneType//�V�[���^�C�v
{
    OPENING,	//�I�[�v�j���O
    TITLE,		//�^�C�g��
    GAME,		//�Q�[��
    GAMECLEAR,	//�G���h
    GAMEOVER,	//�G���h
};

float RadToDeg(float _rad);		// ���V�A����x��
float DegToRad(float _deg);		// �x�����W�A����

bool operator ==(VECTOR _vector1, VECTOR _vector2);

