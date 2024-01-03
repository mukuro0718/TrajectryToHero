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
//���̍쐬�i�`��j�ɕK�v�ȏ��
struct SphereInfo
{
    VECTOR centerPos = ORIGIN_POS;//�����S���W
    float radius = 0.0f;//�����a
    int divNum = 8;//�J�v�Z��������
    int difColor = 0;//�f�B�t���[�Y�J���[
    int spcColor = 0;//�X�y�L�����J���[
    int fillFlag = false;//�`�悷�鋅��h��Ԃ����ǂ���
};
//�t�H���g�̕`��ɕK�v�ȏ��
struct FontInfo
{
    int size = 0;//�t�H���g�̑傫��
    int thick = 0;//�t�H���g�̑���
    int type = 0;//�t�H���g�^�C�v
};
//�A�i���O�X�e�B�b�N���͕ϐ�
struct InputAnalogStick
{
    int XBuf = 0;//���E�̓��͏�Ԃ��i�[
    int YBuf = 0;//�㉺�̓��͏�Ԃ��i�[
};
//�QD�x�N�g���\����
struct VEC2D
{
    int x = 0;
    int y = 0;
};
//�`��͈�
struct DrawRect
{
    int lx = 0;
    int ly = 0;
    int rx = 0;
    int ry = 0;
};
//�V�[���^�C�v
enum class SceneType:int
{
    OPENING,	//�I�[�v�j���O
    TITLE,		//�^�C�g��
    GAME,		//�Q�[��
    GAMECLEAR,	//�N���A
    GAMEOVER,	//�G���h
};
float RadToDeg(float _rad);		// ���V�A����x��
float DegToRad(float _deg);		// �x�����W�A����

bool operator ==(VECTOR _vector1, VECTOR _vector2);

