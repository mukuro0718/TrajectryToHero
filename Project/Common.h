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

//�J�v�Z���̍쐬�i�`��j�ɕK�v�ȏ��
struct CapsuleInfo
{
    VECTOR topPos   = ORIGIN_POS;//�J�v�Z���㕔���W
    VECTOR underPos = ORIGIN_POS;//�J�v�Z���������W
    float radius    = 0.0f      ;//���a
    int divNum      = 8         ;//�J�v�Z��������
    int difColor    = 0         ;//�f�B�t���[�Y�J���[
    int spcColor    = 0         ;//�X�y�L�����J���[
    int fillFlag    = false     ;//�`�悷�鋅��h��Ԃ����ǂ���
};
struct FontInfo//�t�H���g�̕`��ɕK�v�ȏ��
{
    int size = 0;//�t�H���g�̑傫��
    int thick = 0;//�t�H���g�̑���
    int type = 0;//�t�H���g�^�C�v
};

struct InputAnalogStick//�A�i���O�X�e�B�b�N���͕ϐ�
{
    int XBuf = 0;//���E�̓��͏�Ԃ��i�[
    int YBuf = 0;//�㉺�̓��͏�Ԃ��i�[
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

