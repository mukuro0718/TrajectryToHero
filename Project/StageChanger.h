//===========================================================================
//@brief �X�e�[�W�؂�ւ��N���X
//===========================================================================
#pragma once
#include"DxLib.h"
#include"Common.h"
#include<vector>

class Timer;
using namespace std;
class StageChanger
{
public:
    StageChanger();             //�R���X�g���N�^
    ~StageChanger();            //�f�X�g���N�^

    void Init();//������
    void Delete();//�폜
    void DrawImageWhenSwitchingStage();//�E�F�[�u�J�n���̉摜�̕\��
    void DrawGameOver();//�Q�[���I�����̉摜�̕\��
    void DrawGameClear();//�Q�[���N���A�̉摜�̕\��
    void Draw();
    VECTOR DrawAlert(VECTOR playerPos);//farm_boss�̃X�e�[�W�ړ����s�����ǂ���

    //�X�e�[�W�؂�ւ��t���O�i�؂�ւ����I����Ă��邩�ǂ������Ǘ��j
    const bool GetIsChangeStage()const { return isChangeStage; }
    //�t�@�[���X�e�[�W�t���O��getter/setter
    const bool GetIsFarm()const { return isFarm; }
    //�{�X�X�e�[�W�t���O��getter/setter
    const bool GetIsBoss()const{return isBoss; }
    //�Q�[���I�[�o�[�t���O��getter/setter
    const bool GetIsGameOver()const { return isGameOver; }
    //�Q�[���N���A�t���O��getter/setter
    const bool GetIsGameClear()const { return isGameClear; }
    //�Q�[���I�[�o�[�t���O��getter/setter
    const bool GetIsGameEnd()const { return isGameEnd; }
    //�x���t���O��getter/setter
    const bool GetIsAlert()const { return isDrawAlert; }

private:
    //�萔
    enum class ImageType
    {
        FARM_STAGE, //�t�@�[���X�e�[�W
        BOSS_STAGE,	//�{�X�X�e�[�W
        ALERT, //��ʈÓ]�p
    };
    static constexpr int   IMG_SIZE             = 60;       //�摜�T�C�Y
    static constexpr int   IMAGE_NUM            = 3;        //���摜��
    static constexpr float IMG_ANGLE            = 0.0f;     //�摜�A���O��
    static constexpr float SET_GAMEOVER_TIMER   = 10.0f;    //�^�C�}�[�ڕW����
    static constexpr float SET_STAY_TIMER       = 10.0f;    //�^�C�}�[�ڕW����
    static const VECTOR DRAW_GATEIMAGE_POS;
    //�N���X�E�\����
    Timer* StayMaxAlphaTimer;//�A���t�@�l���ő�̎��ɕ`�悷�鎞��
    VEC2D DrawImagePos;
    //�ϐ�
    vector<int> image;      //�摜�n���h��
    int gateImage;          //�Q�[�g�摜
    int  alpha;             //�A���t�@�l
    int  backGroundAlpha;   //�w�i�A���t�@�l
    int  alphaValue;        //������
    float gateImageAngle;   //�Q�[�g�摜�̉�]�p�x
    bool isFarm;            //�t�@�[���X�e�[�W
    bool isBoss;            //�{�X�X�e�[�W
    bool isChangeStage;     //�X�e�[�W�؂�ւ��t���O
    bool isGameOver;        //�Q�[���I�[�o�[�t���O
    bool isGameClear;       //�Q�[���N���A�t���O
    bool isGameEnd;         //�Q�[���I���t���O
    bool isDrawBlackBack;   //���w�i�`��t���O
    bool isDrawAlert;       //�x���`��t���O(true:�`�悵�Ă��� false:�`�悵�Ă��Ȃ�)
};