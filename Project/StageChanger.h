/*HACK:
�t�@�[���X�e�[�W�ƃ{�X�X�e�[�W�̐؂�ւ����s��
�X�e�[�W�ړ�����������ōs��
�Q�[���I�[�o�[�A�N���A����������ōs��
*/
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

    VECTOR DrawAlert(VECTOR playerPos);//farm_boss�̃X�e�[�W�ړ����s�����ǂ���

    //�X�e�[�W�؂�ւ��t���O�i�؂�ւ����I����Ă��邩�ǂ������Ǘ��j
    const bool GetIsChangeStage()const { return isChangeStage; }
    void SetIsChangeStage(const bool _set) { isChangeStage = _set; }
    //�t�@�[���X�e�[�W�t���O��getter/setter
    const bool GetIsFarm()const { return isFarm; }
    void SetIsFarm(const bool _set) { isFarm = _set; }
    //�{�X�X�e�[�W�t���O��getter/setter
    const bool GetIsBoss()const{return isBoss; }
    void SetIsBoss(const bool _set) { isBoss = _set; }
    //�Q�[���I�[�o�[�t���O��getter/setter
    const bool GetIsGameOver()const { return isGameOver; }
    void SetIsGameOver(const bool _set) { isGameOver = _set; }
    //�Q�[���N���A�t���O��getter/setter
    const bool GetIsGameClear()const { return isGameClear; }
    void SetIsGameClear(const bool _set) { isGameClear = _set; }
    //�Q�[���I�[�o�[�t���O��getter/setter
    const bool GetIsGameEnd()const { return isGameEnd; }
    void SetIsGameEnd(const bool _set) { isGameEnd = _set; }
    //�x���t���O��getter/setter
    const bool GetIsAlert()const { return isDrawAlert; }
    void SetIsAlert(const bool _set) { isDrawAlert = _set; }

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
    //�N���X�E�\����
    Timer* StayMaxAlphaTimer;//�A���t�@�l���ő�̎��ɕ`�悷�鎞��
    VEC2D DrawImagePos;
    //�ϐ�
    vector<int> image;//�摜�n���h��
    int  alpha;             //�A���t�@�l
    int  backGroundAlpha;   //�w�i�A���t�@�l
    int  alphaValue;        //������
    bool isFarm;            //�t�@�[���X�e�[�W
    bool isBoss;            //�{�X�X�e�[�W
    bool isChangeStage;     //�X�e�[�W�؂�ւ��t���O
    bool isGameOver;        //�Q�[���I�[�o�[�t���O
    bool isGameClear;       //�Q�[���N���A�t���O
    bool isGameEnd;         //�Q�[���I���t���O
    bool isDrawBlackBack;   //���w�i�`��t���O
    bool isDrawAlert;       //�x���`��t���O(true:�`�悵�Ă��� false:�`�悵�Ă��Ȃ�)
};